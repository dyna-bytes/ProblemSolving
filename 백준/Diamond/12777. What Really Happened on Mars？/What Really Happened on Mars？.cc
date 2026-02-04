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
    set<Task*> blocking_tasks; // 나 때문에 멈춰있는 태스크들
    int finish_time;
    bool is_blocked;
};

struct Resource {
    int id;
    int prio_ceiling;
    Task* owner_task;
};

struct System {
    int tick;
    int finished_count;
    int sys_ceiling_val;
    Task* sys_ceiling_owner;
};

// --- Helper Functions ---

// 태스크가 현재 실행 가능한 상태인지 (시작 시간 지남 + 미완료)
bool is_runnable(const Task& t, int tick) {
    return t.finish_time == 0 && t.start_time <= tick;
}

// 재귀적으로 자신을 차단한 태스크들을 따라가며 최대 우선순위 계산 (Priority Inheritance)
int calculate_effective_priority(Task& task) {
    int max_prio = task.base_prio;
    for (Task* blocked_task : task.blocking_tasks) {
        max_prio = max(max_prio, calculate_effective_priority(*blocked_task));
    }
    return max_prio;
}

// --- Logic Steps ---

// [Step 1] 현재 시스템 천장 (System Priority Ceiling) 계산
// 반환값: {최고 천장 값, 그 리소스를 가진 태스크 포인터}
void get_system_ceiling(vector<Resource>& resources, System& sys) {
    int max_ceil = -1;
    Task* ceiling_owner = nullptr;

    for (Resource& res: resources) {
        if (res.owner_task) {
            if (res.prio_ceiling > max_ceil) {
                max_ceil = res.prio_ceiling;
                ceiling_owner = res.owner_task;
            }
        }
    }

    sys.sys_ceiling_val = max_ceil;
    sys.sys_ceiling_owner = ceiling_owner;
}

// 차단 관계 형성
void set_blocking_graph(vector<Task>& tasks, vector<Resource>& resources, System& sys) {
    // 1. 시스템 천장 계산 (이번 틱에서 불변)
    int sys_ceiling_val = sys.sys_ceiling_val;
    Task* sys_ceiling_owner = sys.sys_ceiling_owner;

    // 2. 차단 그래프 (Dependency Graph) 구축
    for (Task& task: tasks) {
        if (!is_runnable(task, sys.tick)) continue;

        if (task.pc < task.instructions.size() && task.instructions[task.pc].op == LOCK) {
            int r_id = task.instructions[task.pc].val;
            Resource& target_res = resources[r_id];

            Task* direct_owner = target_res.owner_task;

            // A. 직접 차단 (Direct Blocking)
            // 내가 잡으려는 리소스를 다른 태스크가 잡고 있는 경우
            if (direct_owner && direct_owner != &task) {
                direct_owner->blocking_tasks.insert(&task);
                task.is_blocked = true;
            }
            // B. 천장 차단 (Priority Ceiling Blocking)
            // 내가 그 리소스를 가지고 있지 않고, 내 우선순위가 시스템 천장보다 높지 않다면
            else if (sys_ceiling_owner && sys_ceiling_owner != &task) {
                if (task.curr_prio <= sys_ceiling_val) {
                    sys_ceiling_owner->blocking_tasks.insert(&task);
                    task.is_blocked = true;
                }
            }
        }
    }
}

void unset_blocking_graph(vector<Task>& tasks, vector<Resource>& resources, System& sys) {
    for (Task& task: tasks) {
        if (task.is_blocked && is_runnable(task, sys.tick)) {
            int r_id = task.instructions[task.pc].val;
            Resource& target_res = resources[r_id];

            // 직접 차단이 아닌 경우 (= 천장 차단인 경우)
            if (target_res.owner_task == nullptr) {
                if (task.curr_prio > sys.sys_ceiling_val) {
                    // 상속받은 우선순위가 천장을 뚫음 -> 차단 해제
                    sys.sys_ceiling_owner->blocking_tasks.erase(&task);
                    task.is_blocked = false;
                }
            }
        }
    }
}

// [Step 2 & 3] 차단 관계 형성 및 우선순위 갱신
void synchronize_state(vector<Task>& tasks, vector<Resource>& resources, System& sys) {
    // 1. 차단 관계 초기화
    for (Task& task: tasks) {
        task.blocking_tasks.clear();
        task.is_blocked = false;
        task.curr_prio = task.base_prio;
    }

    // 2. 시스템 천장 계산
    get_system_ceiling(resources, sys);

    // 3. 차단 그래프 구축
    set_blocking_graph(tasks, resources, sys);

    // 4. 우선순위 상속
    for (Task& task: tasks) {
        if (is_runnable(task, sys.tick))
            task.curr_prio = calculate_effective_priority(task);
    }

    // 5. 우선순위 상속 후 천장 차단 재검사
    unset_blocking_graph(tasks, resources, sys);
}

// [Step 3] 실행할 태스크 선정 (Scheduler)
Task* select_next_task(vector<Task>& tasks, System& sys) {
    Task* candidate = nullptr;
    int max_prio = -1;

    for (Task& task : tasks) {
        // 실행 가능하고 차단되지 않은 태스크 중 우선순위가 가장 높은 것
        if (is_runnable(task, sys.tick) && !task.is_blocked) {
            if (task.curr_prio > max_prio) {
                max_prio = task.curr_prio;
                candidate = &task;
            }
        }
    }
    return candidate;
}

// [Step 4] 명령어 실행
void execute_instruction(Task* runner, vector<Resource>& resources, System& sys) {
    // 실행할 태스크가 없으면 시간만 흐름 (Idle)
    if (runner == nullptr) {
        sys.tick++;
        return;
    }

    Instruction& inst = runner->instructions[runner->pc];

    if (inst.op == CALC) {
        // 계산은 시간 소모
        sys.tick++;
        runner->pc++;
    }
    else if (inst.op == LOCK) {
        // 락 획득 (시스템 로직상 시간 소모 0 가정)
        Resource& resource = resources[inst.val];
        resource.owner_task = runner;
        runner->held_resources.push_back(&resource);
        runner->pc++;
    }
    else if (inst.op == UNLOCK) {
        // 락 해제 (시간 소모 0)
        Resource& resource = resources[inst.val];
        resource.owner_task = nullptr;
        runner->held_resources.pop_back();
        runner->pc++;
    }

    // 태스크 완료 체크
    if (runner->pc >= runner->instructions.size()) {
        runner->finish_time = sys.tick;
        sys.finished_count++;
    }
}

// --- Main Solver ---

vector<int> solve(int T, int R, vector<Task>& tasks, vector<Resource>& resources) {
    vector<int> ret(T);
    System sys = {};
    int& tick = sys.tick = 0;
    int& finished_count = sys.finished_count = 0;

    while (finished_count < T) {
        // 1. 차단 상태 및 우선순위 최신화
        synchronize_state(tasks, resources, sys);

        // 2. 다음에 실행할 태스크 선정
        Task* runner = select_next_task(tasks, sys);

        // 3. 명령어 실행 (Tick 증가 포함)
        execute_instruction(runner, resources, sys);
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