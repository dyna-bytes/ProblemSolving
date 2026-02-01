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

    vector<int> held_resources;
    set<int> blocking_tasks;
    int finish_time;
    bool is_blocked;
};

struct Resource {
    int id;
    int prio_ceiling;
    int owner_task;
};

bool check_block(int t_id, int r_id, vector<Task>& tasks, vector<Resource>& resources) {
    bool blocked_now = false;
    Task& t = tasks[t_id];

    int owner = resources[r_id].owner_task;
    if (owner && owner != t_id) {
        tasks[owner].blocking_tasks.insert(t_id);
        blocked_now = true;
    }

    for (int r = 1; r < resources.size(); r++) {
        int r_owner = resources[r].owner_task;
        if (r_owner && r_owner != t_id) {
            if (resources[r].prio_ceiling >= t.curr_prio) {
                tasks[r_owner].blocking_tasks.insert(t_id);
                blocked_now = true;
            }
        }
    }

    return (t.is_blocked = blocked_now);
}

int get_priority(int task_id, vector<Task>& tasks) {
    Task& t = tasks[task_id];
    int max_prio = t.base_prio;

    for (int blocked_id: t.blocking_tasks)
        max_prio = max(max_prio, get_priority(blocked_id, tasks));
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

            for (int i = 1; i <= T; i++)
                tasks[i].blocking_tasks.clear();

            for (int i = 1; i <= T; i++) {
                Task& t = tasks[i];
                if (!is_running(t, tick)) {
                    t.is_blocked = false;
                    continue;
                }

                if (t.pc < t.instructions.size() && t.instructions[t.pc].op == LOCK) {
                    int r_id = t.instructions[t.pc].val;
                    t.is_blocked = check_block(i, r_id, tasks, resources);
                } else
                    t.is_blocked = false;
            }

            for (int i = 1; i <= T; i++) {
                if (is_running(tasks[i], tick)) {
                    int new_prio = get_priority(i, tasks);
                    if (tasks[i].curr_prio != new_prio) {
                        tasks[i].curr_prio = new_prio;
                        changed = true;
                    }
                }
            }

            if (!changed) break;
        }

        int runner_id = -1;
        int max_prio = -1;
        for (int i = 1; i <= T; i++) {
            Task& t = tasks[i];
            if (is_running(t, tick) && !t.is_blocked) {
                if (t.curr_prio > max_prio) {
                    max_prio = t.curr_prio;
                    runner_id = i;
                }
            }
        }

        if (runner_id == -1) {
            tick++;
            continue;
        }

        Task& runner = tasks[runner_id];
        Instruction& inst = runner.instructions[runner.pc];

        if (inst.op == CALC) {
            tick++;
            runner.pc++;
        } else if (inst.op == LOCK) {
            int r_id = inst.val;
            resources[r_id].owner_task = runner_id;
            runner.held_resources.push_back(r_id);
            runner.pc++;
        } else if (inst.op == UNLOCK) {
            int r_id = inst.val;
            resources[r_id].owner_task = 0;
            runner.held_resources.pop_back();
            runner.pc++;
        }

        if (runner.pc >= runner.instructions.size()) {
            runner.finish_time = tick;
            finished_count++;
        }
    }

    for (int i = 1; i <= T; i++) ret[i-1] = tasks[i].finish_time;
    return ret;
}

int main() {
    FASTIO;
    int T, R;
    cin >> T >> R;

    vector<Task> tasks(T + 1); // one-base indexing
    vector<Resource> resources(R + 1); // one-base indexing
    for (int i = 1; i <= R; i++)
        resources[i].id = i;

    for (int i = 1; i <= T; i++) {
        Task& t = tasks[i];
        t.id = i;
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
                t.instructions.push_back({op, val});

                resources[val].prio_ceiling = max(
                    resources[val].prio_ceiling, t.base_prio
                );
            } else if (op == 'U') {
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