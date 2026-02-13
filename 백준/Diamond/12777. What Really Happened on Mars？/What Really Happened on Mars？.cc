#include <iostream>
#include <bits/stdc++.h>

using namespace std;
#define endl '\n'
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
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

const char OP_LOCK = 'L';
const char OP_UNLOCK = 'U';
const char OP_CACL = 'C';

enum TaskState {
    INACTIVE,   // 시작 전
    READY,      // 실행 대기 (Ready Queue)
    RUNNING,    // CPU 점유 중
    BLOCKED,    // 리소스 대기 (Wait Queue)
    FINISHED    // 종료됨
};

// --- Forward Declarations ---
struct Task;
struct Resource;

// --- Structures ---
struct Instruction {
    char op;
    int val;
};

struct Task {
    int id;
    int start_time;
    int base_prio;
    int curr_prio; // 상속된 우선순위

    TaskState state;

    int pc; // Program Counter
    vector<Instruction> instructions;

    vector<Resource*> held_resources;
    set<Task*> blocking_tasks; // 나 때문에 멈춰있는 태스크들 (상속 계산용)

    int finish_time;
};

struct Resource {
    int id;
    int prio_ceiling;
    Task* owner_task;
};

// --- RTOS Kernel Class ---
class Kernel {
private:
    int tick;
    int total_tasks;
    int finished_count;

    Task* current_task;
    vector<Task*> ready_queue;
    vector<Task*> wait_queue;

    vector<Resource>& resources;
    vector<Task>& tasks;
public:
    Kernel(int T, vector<Task>& t, vector<Resource>& r)
        : total_tasks(T), tasks(t), resources(r), tick(0),
        finished_count(0), current_task(nullptr) {}

    // ---------------------------------------------------------
    // 1. Kernel Utilities (Priority & Ceiling)
    // ---------------------------------------------------------
    int calculate_inherited_priority(Task* t) {
        int max_prio = t->base_prio;
        for (Task* blocked: t->blocking_tasks)
            max_prio = max(max_prio, calculate_inherited_priority(blocked));
        return max_prio;
    }

    void update_priority(Task* t) {
        t->curr_prio = calculate_inherited_priority(t);
    }

    pair<int, Task*> get_system_ceiling() {
        int max_ceil = -1;
        Task* owner = nullptr;
        for (const auto& resource: resources) {
            if (resource.owner_task) {
                if (resource.prio_ceiling > max_ceil) {
                    max_ceil = resource.prio_ceiling;
                    owner = resource.owner_task;
                }
            }
        }
        return { max_ceil, owner };
    }

    // ---------------------------------------------------------
    // 2. Queue Management (Scheduling Logic)
    // ---------------------------------------------------------
    void enqueue_ready(Task* t) {
        if (t->state == READY || t->state == RUNNING) return;

        t->state = READY;
        ready_queue.push_back(t);
    }

    void enqueue_wait(Task* t) {
        t->state = BLOCKED;
        wait_queue.push_back(t);
    }

    void schedule() {
        if (current_task) {
            if (current_task->state == RUNNING) {
                current_task->state = INACTIVE;
                enqueue_ready(current_task);
            }
            current_task = nullptr;
        }

        if (ready_queue.empty()) return;

        auto best_it = ready_queue.begin();
        for (auto it = ready_queue.begin(); it != ready_queue.end(); ++it) {
            Task* t = *it;
            Task* best = *best_it;
            if (t->curr_prio > best->curr_prio)
                best_it = it;
        }

        current_task = *best_it;
        ready_queue.erase(best_it);
        current_task->state = RUNNING;
    }

    // ---------------------------------------------------------
    // 3. System Calls (LOCK, UNLOCK)
    // ---------------------------------------------------------
    bool sys_lock(Task* task, int r_id) {
        Resource& res = resources[r_id];
        auto [sys_ceil, sys_ceil_owner] = get_system_ceiling();

        Task* blocker = nullptr;
        if (res.owner_task)
            blocker = res.owner_task;
        else if (sys_ceil_owner && sys_ceil_owner != task)
            if (task->curr_prio <= sys_ceil)
                blocker = sys_ceil_owner;

        if (blocker) {
            enqueue_wait(task);
            blocker->blocking_tasks.insert(task);

            update_priority(blocker);
            for (auto& t: tasks) update_priority(&t);
            return false;
        }

        res.owner_task = task;
        task->held_resources.push_back(&res);
        return true;
    }

    void sys_unlock(Task* task, int r_id) {
        Resource& res = resources[r_id];

        res.owner_task = nullptr;
        task->held_resources.pop_back();

        for (auto& t: tasks) t.blocking_tasks.clear();
        for (auto& t: tasks) update_priority(&t);

        for (Task* t: wait_queue)
            enqueue_ready(t);

        wait_queue.clear();
    }

    // ---------------------------------------------------------
    // 4. Main Kernel Loop
    // ---------------------------------------------------------
    void run() {
        while (finished_count < total_tasks) {
            for (auto& t: tasks) {
                if (t.state == INACTIVE && t.start_time <= tick) {
                    t.curr_prio = t.base_prio;
                    enqueue_ready(&t);
                }
            }

            schedule();

            if (!current_task) {
                tick++;
                continue;
            }

            Instruction& inst = current_task->instructions[current_task->pc];

            switch (inst.op)
            {
            case OP_CACL:
                tick++;
                current_task->pc++;
                break;
            case OP_LOCK:
                if (sys_lock(current_task, inst.val))
                    current_task->pc++;
                break;
            case OP_UNLOCK:
                sys_unlock(current_task, inst.val);
                current_task->pc++;
                break;
            default:
                break;
            }

            if (current_task->state == RUNNING
            && current_task->pc >= current_task->instructions.size()) {
                current_task->state = FINISHED;
                current_task->finish_time = tick;
                finished_count++;
            }
        }
    }
};

// --- Main ---
int main() {
    FASTIO;
    int T, R;
    cin >> T >> R;

    vector<Task> tasks(T);
    vector<Resource> resources(R);
    for (int i = 0; i < R; i++) {
        resources[i].id = i + 1;
        resources[i].owner_task = nullptr;
        resources[i].prio_ceiling = 0; // 초기화
    }

    for (int i = 0; i < T; i++) {
        Task& t = tasks[i];
        t.id = i + 1;
        t.state = INACTIVE; // 초기 상태
        cin >> t.start_time >> t.base_prio;
        t.curr_prio = t.base_prio;

        int inst_size; cin >> inst_size;
        t.instructions.reserve(inst_size);

        for (int k = 0; k < inst_size; k++) {
            string in;
            cin >> in;
            char op = in[0];
            int val = stoi(in.substr(1));

            if (op == 'L') {
                val--; // 0-based
                t.instructions.push_back({op, val});
                resources[val].prio_ceiling = max(resources[val].prio_ceiling, t.base_prio);
            } else if (op == 'U') {
                val--; // 0-based
                t.instructions.push_back({op, val});
            } else if (op == 'C') {
                for(int m=0; m<val; m++) t.instructions.push_back({op, 1});
            }
        }
    }

    Kernel kernel(T, tasks, resources);
    kernel.run();

    for (int i = 0; i < T; i++) {
        cout << tasks[i].finish_time << endl;
    }

    return 0;
}