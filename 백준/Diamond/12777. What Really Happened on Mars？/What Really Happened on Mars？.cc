#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define DBG
#ifdef DBG
#define debug(x) cout << "[" << __func__ << "](" << __LINE__ << ") " << #x << " is " << x << endl;
#define debugVect(v) do { \
    cout << "[" << __func__ << "](" << __LINE__ << ") " << #v << " is |\t"; \
    for (auto e: v) cout << e << "|\t" ; \
    cout << endl; \
} while (0)
#define debugVect2d(vv) do { \
    cout << "[" << __func__ << "](" << __LINE__ << ") " << #vv << " is " << endl; \
    for (auto v: vv) debugVect(v); \
} while (0)
#else
#define debug(x)
#define debugVect(v)
#define debugVect2d(vv)
#endif

const char LOCK = 'L';
const char UNLOCK = 'U';
const char CALC = 'C';

struct Task;
struct Resource;

struct Instruction {
    char op;
    int val;
};

struct Task {
    int id;
    int start_time;
    int base_prio;
    int curr_prio;

    int pc;
    vector<Instruction> instructions;

    vector<Resource*> held_resources;
    set<Task*> blocking_tasks;
    int finish_time;
    bool is_blocked;
};

struct Resource {
    int id;
    int prio_ceiling;
    Task* owner_task;
};

bool check_block(Task& task, Resource& resource, vector<Task>& tasks, vector<Resource>& resources) {
    bool blocked_now = false;

    Task* owner = resource.owner_task;
    if (owner && owner != &task) {
        owner->blocking_tasks.insert(&task);
        blocked_now = true;
    }

    for (Resource& resource: resources) {
        Task* r_owner = resource.owner_task;
        if (r_owner && r_owner != &task) {
            if (resource.prio_ceiling >= task.curr_prio) {
                r_owner->blocking_tasks.insert(&task);
                blocked_now = true;
            }
        }
    }

    return (task.is_blocked = blocked_now);
}

int get_priority(Task& task) {
    int max_prio = task.base_prio;

    for (Task* blocked_task: task.blocking_tasks)
        max_prio = max(max_prio, get_priority(*blocked_task));
    return max_prio;
}

vector<int> solve(int T, int R, vector<Task>& tasks, vector<Resource>& resources) {
    int tick = 0;
    int finished_count = 0;
    vector<int> ret(T);

    auto is_running = [](Task& t, int tick) {
        return t.finish_time == 0 && t.start_time <= tick;
    };

    while (finished_count < T) {

        while (true) {
            bool changed = false;

            for (Task& task: tasks)
                task.blocking_tasks.clear();

            for (Task& task: tasks) {
                if (!is_running(task, tick)) {
                    task.is_blocked = false;
                    continue;
                }

                if (task.pc < task.instructions.size() && task.instructions[task.pc].op == LOCK) {
                    int r_id = task.instructions[task.pc].val;
                    Resource& resource = resources[r_id];
                    task.is_blocked = check_block(task, resource, tasks, resources);
                } else
                    task.is_blocked = false;
            }

            for (Task& task: tasks) {
                if (is_running(task, tick)) {
                    int new_prio = get_priority(task);
                    if (task.curr_prio != new_prio) {
                        task.curr_prio = new_prio;
                        changed = true;
                    }
                }
            }

            if (!changed) break;
        }

        Task* runner_task = nullptr;
        int max_prio = -1;
        for (Task& task: tasks) {
            if (is_running(task, tick) && !task.is_blocked) {
                if (task.curr_prio > max_prio) {
                    max_prio = task.curr_prio;
                    runner_task = &task;
                }
            }
        }

        if (runner_task == nullptr) {
            tick++;
            continue;
        }

        Task& runner = *runner_task;
        Instruction& inst = runner.instructions[runner.pc];

        if (inst.op == CALC) {
            tick++;
            runner.pc++;
        } else if (inst.op == LOCK) {
            Resource& resource = resources[inst.val];
            resource.owner_task = runner_task;
            runner.held_resources.push_back(&resource);
            runner.pc++;
        } else if (inst.op == UNLOCK) {
            Resource& resource = resources[inst.val];
            resource.owner_task = nullptr;
            runner.held_resources.pop_back();
            runner.pc++;
        }

        if (runner.pc >= runner.instructions.size()) {
            runner.finish_time = tick;
            finished_count++;
        }
    }

    for (int i = 0; i < T; i++) ret[i] = tasks[i].finish_time;
    return ret;
}

int main() {
    FASTIO;
    int T, R;
    cin >> T >> R;

    vector<Task> tasks(T);
    vector<Resource> resources(R);
    for (int i = 0; i < R; i++)
        resources[i].id = i + 1;

    for (int i = 0; i < T; i++) {
        Task& t = tasks[i];
        t.id = i + 1;
        cin >> t.start_time >> t.base_prio;

        int inst_size; cin >> inst_size;
        t.instructions.reserve(inst_size * 100);
        t.instructions.clear();

        for (int k = 0; k < inst_size; k++) {
            string in;
            cin >> in;

            char op = in[0];
            int val = stoi(in.substr(1));

            if (op == 'L') {
                val--; // zero based indexing
                t.instructions.push_back({op, val});

                resources[val].prio_ceiling = max(
                    resources[val].prio_ceiling, t.base_prio
                );
            } else if (op == 'U') {
                val--;
                t.instructions.push_back({op, val});
            } else if (op == 'C') {
                for (int m = 0; m < val; m++)
                    t.instructions.push_back({op, 1});
            }
        }
    }

    vector<int> ret = solve(T, R, tasks, resources);
    for (int r: ret)
        cout << r << endl;

    return 0;
}