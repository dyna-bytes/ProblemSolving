#include <iostream>
#include <bits/stdc++.h>

using namespace std;
#define endl '\n'
#define FASTIO ios::sync_with_stdio(0), cin.tie(0)

// #define DBG
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


// ==========================================
// [Kernel Constants & Enums]
// ==========================================
#define MAX_CPUS 100

enum TaskState {
    TASK_RUNNING = 0,
    TASK_READY,
    TASK_INTERRUPTIBLE, // Waiting for Semaphore (Blocked)
    TASK_DEAD,          // Terminated
    TASK_ZOMBIE         // Killed but resources not fully reclaimed (optional)
};

enum OpType {
    OP_COMPUTE, OP_FORK_R, OP_FORK_I, OP_YIELD, OP_KILL,
    OP_LOCK, OP_UNLOCK, OP_LOOP, OP_NEXT, OP_END
};

// ==========================================
// [Data Structures]
// ==========================================

// Instruction Format (Machine Code)
struct Instruction {
    OpType opcode;
    string s_operand1;
    string s_operand2;
    int i_operand;

    int jump_pc;
};

// Thread Control Block
struct task_struct {
    int pid = 0;                // Thread ID
    int tgid = 0;               // Task Group ID (Virtual Thread Group for Mutual Exclusion)
    TaskState state = TASK_RUNNING;

    int cpu_id = -1;             // 현재 실행 중인 CPU ID (-1 if not running)
    int remaining_computation = 0;  // 남은 Clock (Context Save/Restore)

    // Context (Registers)
    int pc = 0;                 // Program Counter
    string code_block_name;     // 현재 실행 중인 코드 블록 이름
    map<string, int> registers; // Local variables (thread-vars)

    // For Semaphore Wait Queue (Linked List Node 역할)
    string waiting_sem;
    int waiting_amount = 0;

    // Statistics
    int finish_time = 0;

    // 현재 중첩된 루프들의 남은 반복 횟수를 저장하는 스택
    vector<int> loop_counts;
    bool pending_kill = false;

    bool operator==(const task_struct& other) const {
        // Comparison logic here, e.g.:
        return this->pid == other.pid;
    }
};

// Semaphore Object
struct semaphore {
    int value;
    deque<int> wait_list; // Waiting Tasks (PIDs)
};

// ==========================================
// [Kernel Subsystem]
// ==========================================

class Kernel {
protected:
    // System Resources
    int sys_clock;
    int max_time;
    int max_threads;
    int nr_cpus;
    int time_slice;

    // Memory & Process Management
    map<string, vector<Instruction>> text_segment;  // Code memory
    map<string, semaphore> sem_table;               // IPC table

    // Scheduler Structures
    deque<task_struct*> runqueue;           // Global Ready Queue
    task_struct* current[MAX_CPUS];         // Per-CPU current task
    map<int, task_struct> task_table;       // Process Table (All tasks) {pid: task}

    int next_pid = 1;
    bool system_panic = false;

public:
    Kernel(int mt, int mth, int ncpu, int ts)
        : max_time(mt), max_threads(mth), nr_cpus(ncpu), time_slice(ts) {
        sys_clock = 0;
        // CPU 초기화
        for(int i=0; i<MAX_CPUS; i++) current[i] = nullptr;
    }

    // ---------------------------------------------------------
    // [System Call Interface] - 명령어 해석기에서 호출
    // ---------------------------------------------------------

    // Process Creation (fork)
    int sys_fork(task_struct* parent, string var_name, string block_name, bool is_virtual) {
        int living_threads = 0;
        for (auto& [pid, t] : task_table)
            if (t.state != TASK_DEAD) living_threads++;

        if (living_threads >= max_threads)
            return -1;

        task_struct task;
        task.pid = next_pid++;
        if (is_virtual) {
            task.tgid = parent->pid;
        } else {
            task.tgid = task.pid;
        }

        task.state = TASK_READY;
        task.pc = 0;
        task.cpu_id = -1;
        task.code_block_name = block_name;
        task.remaining_computation = 0;
        task.waiting_amount = 0;

        task_table[task.pid] = task;
        runqueue.push_back(&task_table[task.pid]); // Add to Runqueue
        parent->registers[var_name] = task.pid;
        return 0;
    }

    // Semaphore Operations
    void sys_lock(task_struct* task, string sem_name, int amount) {
        semaphore& sem = sem_table[sem_name];
        if (sem.value >= amount) {
            sem.value -= amount;
        } else {
            task->state = TASK_INTERRUPTIBLE;
            task->waiting_sem = sem_name;
            task->waiting_amount = amount;
            current[task->cpu_id] = nullptr;
            sem.wait_list.push_back(task->pid);
        }
    }
    void sys_unlock(task_struct* task, string sem_name, int amount) {
        semaphore& sem = sem_table[sem_name];
        if (task->state == TASK_INTERRUPTIBLE) {
            auto& wait_list = sem.wait_list;
            auto find_it = find(wait_list.begin(), wait_list.end(), task->pid);
            if (find_it != wait_list.end())
                wait_list.erase(find_it);
        }

        sem.value += amount;

        while (!sem.wait_list.empty()) {
            int next_pid = sem.wait_list.front();
            task_struct* next = &task_table[next_pid];

            if (sem.value < next->waiting_amount) break;
            sem.value -= next->waiting_amount;
            next->waiting_amount = 0;
            next->waiting_sem = "";
            next->state = TASK_READY;
            runqueue.push_back(next);
            sem.wait_list.pop_front();
        }
    }

    // Signal Handling
    void sys_kill(task_struct* sender, string target_var_name) {
        if (sender->registers.find(target_var_name) == sender->registers.end()) return;
        int target_pid = sender->registers[target_var_name];

        if (task_table.find(target_pid) == task_table.end()) return;
        task_struct* target = &task_table[target_pid];

        if (target->state == TASK_RUNNING) {
            current[target->cpu_id] = nullptr;
            target->state = TASK_DEAD;
            target->finish_time = sys_clock;
        } else if (target->state == TASK_READY) {
            target->pending_kill = true;
        } else if (target->state == TASK_INTERRUPTIBLE) {
            semaphore& sem = sem_table[target->waiting_sem];
            deque<int>& wait_list = sem.wait_list;
            auto find_it = find(wait_list.begin(), wait_list.end(), target->pid);
            if (find_it != wait_list.end())
                wait_list.erase(find_it);

            target->state = TASK_READY;
            target->waiting_sem = "";
            runqueue.push_back(target);
            target->pending_kill = true;
        }
    }

    // Yield
    void sys_yield(task_struct* task) {
        current[task->cpu_id] = nullptr;
        task->state = TASK_READY;
        task->cpu_id = -1;
        runqueue.push_back(task);
    }

    // ---------------------------------------------------------
    // [Core Kernel Logic] - 사용자 구현 영역
    // ---------------------------------------------------------

    // [TODO] 1. 인터럽트 핸들러: 매 Time Step마다 호출
    // - Round Robin 스케줄링 정책 적용 (Time Slice 만료 시 선점)
    void scheduler_tick() {
        // Hint: if (sys_clock % time_slice == 0) -> Preempt all running tasks
        if (sys_clock % time_slice == 0) {
            for (int cpu = 0; cpu < nr_cpus; ++cpu) {
                if (!current[cpu]) continue;
                current[cpu]->state = TASK_READY;
                current[cpu]->cpu_id = -1;
                runqueue.push_back(current[cpu]);
                current[cpu] = nullptr;
            }
        }
    }

    // [TODO] 2. 메인 스케줄러
    // - Ready Queue에서 태스크를 꺼내 CPU에 할당 (Dispatcher)
    // - forkI (Virtual Thread) 상호 배제 제약 조건 검사
    task_struct* schedule(int cpu) {
        for (auto it = runqueue.begin(); it != runqueue.end(); ++it) {
            if (is_group_running((*it)->tgid)) continue; // 상호 배제

            task_struct* task = *it;
            runqueue.erase(it);

            task->state = TASK_RUNNING;
            task->cpu_id = cpu;
            current[cpu] = task;
            return task;
        }
        return nullptr;
    }

    // [Refactoring 1] 지연 종료 로직 분리
    bool handle_deferred_kill(int cpu, task_struct* task) {
        if (task && task->pending_kill) {
            task->state = TASK_DEAD;
            task->finish_time = sys_clock;
            current[cpu] = nullptr;
            return true; // 사형 집행 완료
        }
        return false;
    }

    // [Refactoring 2] 단일 명령어 실행기 분리
    // - ret: 에러 코드 (system panic 등)
    // - break_tick: 참조(reference)로 전달하여 현재 틱의 파이프라인을 멈출지 결정
    int execute_instruction(int cpu, task_struct* task, Instruction& inst, bool& break_tick) {
        int ret = 0;
        switch (inst.opcode) {
            case OP_COMPUTE: {
                task->remaining_computation = inst.i_operand;
                task->pc++;
                break_tick = true;
                break;
            }
            case OP_YIELD: {
                sys_yield(task);
                task->pc++;
                break_tick = true;
                break;
            }
            case OP_LOCK: {
                sys_lock(task, inst.s_operand1, inst.i_operand);
                task->pc++;
                if (task->state == TASK_INTERRUPTIBLE) {
                    break_tick = true;
                }
                break;
            }
            case OP_END: {
                for (auto& [sem_name, sem] : sem_table) {
                    auto& wait_list = sem.wait_list;
                    auto find_it = find(wait_list.begin(), wait_list.end(), task->pid);
                    if (find_it != wait_list.end()) wait_list.erase(find_it);
                }
                task->state = TASK_DEAD;
                task->finish_time = sys_clock;
                current[cpu] = nullptr;
                break_tick = true;
                break;
            }
            case OP_LOOP: {
                if (inst.i_operand == 0) task->pc = inst.jump_pc + 1;
                else { task->loop_counts.push_back(inst.i_operand); task->pc++; }
                break;
            }
            case OP_NEXT: {
                int& current_loop = task->loop_counts.back();
                current_loop--;
                if (current_loop > 0) task->pc = inst.jump_pc + 1;
                else { task->loop_counts.pop_back(); task->pc++; }
                break;
            }
            case OP_FORK_R: {
                ret = sys_fork(task, inst.s_operand1, inst.s_operand2, false);
                if (ret) return ret;
                task->pc++; break;
            }
            case OP_FORK_I: {
                ret = sys_fork(task, inst.s_operand1, inst.s_operand2, true);
                if (ret) return ret;
                task->pc++; break;
            }
            case OP_UNLOCK: {
                sys_unlock(task, inst.s_operand1, inst.i_operand);
                task->pc++; break;
            }
            case OP_KILL: {
                sys_kill(task, inst.s_operand1);
                task->pc++; break;
            }
        }
        return ret;
    }

    // [TODO] 3. 오케스트레이터로 가벼워진 run_cpus
    int run_cpus() {
        int ret = 0;
        for (int cpu = 0; cpu < nr_cpus; ++cpu) {
            while (true) {
                task_struct* task = current[cpu];

                // 1. CPU가 비어있다면 즉시 스케줄링 시도
                if (!task) {
                    task = schedule(cpu);
                    if (!task) break;
                }

                // 2. 지연 종료 (Deferred Kill) 처리
                if (handle_deferred_kill(cpu, task)) {
                    continue; // 죽었으면 while 처음으로 돌아가 다음 태스크 스케줄링
                }

                // 3. 연산(compute) 중이면 명령어 실행 건너뜀
                if (task->remaining_computation > 0) {
                    break;
                }

                vector<Instruction>& text = text_segment[task->code_block_name];
                bool break_tick = false;

                // 4. 한 틱 내 명령어 연속 실행 파이프라인
                while (!break_tick && task->state == TASK_RUNNING) {
                    Instruction& inst = text[task->pc];

                    // 단일 명령어 실행기 호출
                    ret = execute_instruction(cpu, task, inst, break_tick);
                    if (ret) return ret; // Panic 발생 시 즉시 탈출
                }

                // 파이프라인 종료 후 여전히 CPU를 점유 중이면 루프 탈출
                if (current[cpu] != nullptr) {
                    break;
                }
            }
        }

        // 5. 남은 연산 시간 차감
        for (int cpu = 0; cpu < nr_cpus; ++cpu) {
            task_struct* task = current[cpu];
            if (task && task->remaining_computation > 0) {
                task->remaining_computation--;
            }
        }
        return ret;
    }

    // [Helper] 그룹 실행 여부 확인 (for forkI)
    bool is_group_running(int tgid) {
        // 현재 running 상태인 모든 태스크 중 tgid가 일치하는 것이 있는지 검사
        for (int cpu = 0; cpu < nr_cpus; ++cpu) {
            if (!current[cpu]) continue;
            if (current[cpu]->tgid == tgid) return true;
        }
        return false;
    }

    // ---------------------------------------------------------
    // [Entry Point] - 부팅 및 메인 루프
    // ---------------------------------------------------------
    void start_kernel(map<string, int>& init_sems, map<string, vector<Instruction>>& codes, string init_block) {
        int ret = 0;

        // 1. Load Resources
        sem_table.clear();
        for(auto& kv : init_sems) sem_table[kv.first] = {kv.second, {}};
        text_segment = codes;

        // 코드 블록별로 loop와 next 연결하기 (전처리)
        for (auto& [block_name, insts]: text_segment) {
            vector<int> loop_stack;
            for (int pc = 0; pc < insts.size(); ++pc) {
                if (insts[pc].opcode == OP_LOOP) {
                    loop_stack.push_back(pc);
                } else if (insts[pc].opcode == OP_NEXT) {
                    int loop_pc = loop_stack.back();
                    loop_stack.pop_back();

                    insts[loop_pc].jump_pc = pc;
                    insts[pc].jump_pc = loop_pc;
                }
            }
        }

        // 2. Create Init Process (PID 1)
        task_struct init_task;
        init_task.pid = next_pid++;
        init_task.tgid = init_task.pid; // Init task starts its own group
        init_task.state = TASK_READY;
        init_task.pc = 0;
        init_task.cpu_id = -1;
        init_task.code_block_name = init_block;
        init_task.remaining_computation = 0;
        init_task.waiting_amount = 0;

        task_table[init_task.pid] = init_task;
        runqueue.push_back(&task_table[init_task.pid]); // Add to Runqueue

        // 3. Main Kernel Loop
        while (sys_clock <= max_time) {
            // A. Timer Interrupt & Scheduling
            scheduler_tick();

            // B. Execute Instructions
            ret = run_cpus();
            if (ret) {
                system_panic = true;
                break;
            }

            // C. Advance System Clock
            sys_clock++;
        }

        // 4. Print Result (Panic or Shutdown)
        print_result();
    }

    void print_result() {
        bool loop = false;
        for (auto& [pid, task]: task_table)
            if (task.state != TASK_DEAD) {
                loop = true;
                break;
            }

        for (auto& [pid, task]: task_table)
            if (task.state == TASK_DEAD)
                cout << pid << " " << task.finish_time << endl;

        if (system_panic) {
            cout << "<<oops>>" << endl;
            return;
        }

        if (loop)
            cout << "<<loop>>" << endl;
    }
};

// #define TEST
#ifdef TEST
class TestKernel : public Kernel {
public:
    TestKernel(int mt, int mth, int ncpu, int ts) : Kernel(mt, mth, ncpu, ts) {}

#define ASSERT_TEST(cond, msg) \
    if (!(cond)) { \
        cerr << "[FAIL] " << __func__ << ": " << msg << "\n"; \
        return false; \
    }

    // 각 단위 테스트 전 커널의 메모리와 상태를 완전히 초기화
    void reset_unit_test(int mt, int mth, int ncpu, int ts) {
        max_time = mt; max_threads = mth; nr_cpus = ncpu; time_slice = ts;
        sys_clock = 0; next_pid = 1; system_panic = false;
        text_segment.clear(); sem_table.clear(); task_table.clear(); runqueue.clear();
        for (int i = 0; i < MAX_CPUS; i++) current[i] = nullptr;
    }

    // ------------------------------------------------------------------
    // [Unit Test 1] sys_fork : Capacity 방어 (TC4) & Virtual Thread 상속 (TC3)
    // ------------------------------------------------------------------
    bool test_sys_fork_edge_cases() {
        reset_unit_test(10, 2, 1, 5); // ★ 최대 스레드 제한(max_threads)을 2로 설정

        // 1. 초기 상태: 부모 태스크 1개 존재 (living_threads = 1)
        task_struct parent;
        parent.pid = next_pid++; parent.tgid = parent.pid; parent.state = TASK_RUNNING;
        task_table[parent.pid] = parent;

        // Act 1: Virtual Thread (forkI) 생성 시도
        int ret1 = sys_fork(&task_table[parent.pid], "child1", "blockB", true);

        // Assert 1: 성공해야 하며, tgid가 부모와 같고, 부모의 레지스터에 PID가 저장되어야 함 (TC2 시그널 미스 방지)
        ASSERT_TEST(ret1 == 0, "First fork should succeed");
        ASSERT_TEST(task_table[parent.pid].registers["child1"] == 2, "Child PID must be saved to parent's register");
        ASSERT_TEST(task_table[2].tgid == parent.tgid, "Virtual thread MUST inherit parent's tgid");

        // Act 2: Native Thread (forkR) 생성 시도 -> living_threads가 2이므로 여기서 터져야 함!
        int ret2 = sys_fork(&task_table[parent.pid], "child2", "blockC", false);

        // Assert 2: Capacity 초과 방어 로직 검증 (TC4)
        ASSERT_TEST(ret2 == -1, "Second fork MUST fail (max_threads exceeded)");
        ASSERT_TEST(task_table.size() == 2, "No new task should be added to task_table");

        return true;
    }

    // ------------------------------------------------------------------
    // [Unit Test 2] sys_kill : 지연 종료(Deferred Kill)의 정밀한 상태 전이 (TC2)
    // ------------------------------------------------------------------
    bool test_sys_kill_deferred() {
        reset_unit_test(10, 10, 1, 5);

        sem_table["sem1"] = {0, {2}}; // 값 0, PID 2가 대기 중

        // Arrange: Task 1(READY 상태), Task 2(WAITING 상태)
        task_table[1] = {1, 1, TASK_READY};
        task_table[2] = {2, 2, TASK_INTERRUPTIBLE};
        task_table[2].waiting_sem = "sem1";

        // Sender 세팅 (타겟들의 PID 보관)
        task_table[9] = {9, 9, TASK_RUNNING};
        task_table[9].registers["target1"] = 1;
        task_table[9].registers["target2"] = 2;

        // Act 1: READY 상태인 Task 1 공격
        sys_kill(&task_table[9], "target1");

        // Assert 1: 즉사하지 않고 사형 선고만 받아야 함
        ASSERT_TEST(task_table[1].state == TASK_READY, "Task 1 should NOT be DEAD instantly");
        ASSERT_TEST(task_table[1].pending_kill == true, "Task 1 MUST get pending_kill marker");

        // Act 2: INTERRUPTIBLE (Blocked) 상태인 Task 2 공격
        sys_kill(&task_table[9], "target2");

        // Assert 2: 큐에서 탈출하여 READY가 되고 사형 선고를 받아야 함
        ASSERT_TEST(sem_table["sem1"].wait_list.empty(), "Task 2 MUST be removed from sem's wait_list");
        ASSERT_TEST(task_table[2].waiting_sem == "", "Task 2's waiting_sem target must be cleared");
        ASSERT_TEST(task_table[2].state == TASK_READY, "Task 2 MUST become READY");
        ASSERT_TEST(task_table[2].pending_kill == true, "Task 2 MUST get pending_kill marker");
        ASSERT_TEST(runqueue.back()->pid == 2, "Task 2 MUST be pushed to runqueue to be executed(killed) later");

        return true;
    }

    // ------------------------------------------------------------------
    // [Unit Test 3] sys_lock / sys_unlock : Strict FIFO 보장 (TC2 Deadlock 관련)
    // ------------------------------------------------------------------
    bool test_sys_lock_strict_fifo() {
        reset_unit_test(10, 10, 1, 5);

        sem_table["sem1"] = {1, {}}; // 잔여량 1

        task_table[1] = {1, 1, TASK_RUNNING};
        task_table[2] = {2, 2, TASK_RUNNING};
        task_table[3] = {3, 3, TASK_RUNNING}; // unlock 담당

        // Act 1: Task 1이 2를 요구 (부족해서 Block 됨)
        sys_lock(&task_table[1], "sem1", 2);
        ASSERT_TEST(task_table[1].state == TASK_INTERRUPTIBLE, "Task 1 blocked");

        // Act 2: Task 2가 1을 요구 (충분하므로 성공해야 함 - FIFO 큐에 없으므로)
        sys_lock(&task_table[2], "sem1", 1);
        ASSERT_TEST(task_table[2].state == TASK_RUNNING, "Task 2 succeeds because value is enough and it's not blocked");
        ASSERT_TEST(sem_table["sem1"].value == 0, "Semaphore value becomes 0");

        // Act 3: Task 3이 1을 반환 (잔여량 1이 됨)
        sys_unlock(&task_table[3], "sem1", 1);

        // Assert: 큐의 맨 앞에 있는 Task 1은 2가 필요하므로 여전히 깨어나선 안 됨! (Strict FIFO)
        ASSERT_TEST(sem_table["sem1"].value == 1, "Semaphore value is 1");
        ASSERT_TEST(task_table[1].state == TASK_INTERRUPTIBLE, "Task 1 MUST remain blocked (needs 2)");
        ASSERT_TEST(sem_table["sem1"].wait_list.size() == 1, "Task 1 is still in wait_list");

        return true;
    }

    // ------------------------------------------------------------------
    // [Unit Test 4] execute_instruction : Zero-time Pipeline & Deadlock Trap 방어 (TC1, TC2)
    // ------------------------------------------------------------------
    bool test_execute_instruction_pipeline() {
        reset_unit_test(10, 10, 1, 5);

        task_struct task;
        task.pid = 1;
        task.tgid = 1;
        task.state = TASK_RUNNING;
        task.cpu_id = 0;                // ★ 핵심: sys_lock 내부의 current[cpu_id] 접근 시 Segfault 방지
        task.remaining_computation = 0;
        task.pc = 0;
        task.waiting_amount = 0;
        task.pending_kill = false;

        current[0] = &task;

        sem_table["sem1"] = {0, {}};

        bool break_tick = false;

        // Act & Assert 1: 시간 소모가 없는 명령어 (OP_UNLOCK) -> TC1
        Instruction inst_unlock = {OP_UNLOCK, "sem1", "", 1};
        execute_instruction(0, &task, inst_unlock, break_tick);
        ASSERT_TEST(task.pc == 1, "PC MUST increment");
        ASSERT_TEST(break_tick == false, "Zero-time instruction MUST NOT break the tick pipeline");
        ASSERT_TEST(sem_table["sem1"].value == 1, "Unlock executed");

        // Act & Assert 2: 블록되는 명령어 (OP_LOCK) -> TC2 Deadlock 원인 방어
        Instruction inst_lock = {OP_LOCK, "sem1", "", 5}; // 5를 요구하여 무조건 블록됨
        execute_instruction(0, &task, inst_lock, break_tick);

        ASSERT_TEST(task.state == TASK_INTERRUPTIBLE, "Task MUST be blocked");
        ASSERT_TEST(task.pc == 2, "★ PC MUST increment EVEN IF BLOCKED! (Crucial Deadlock Trap fix)");
        ASSERT_TEST(break_tick == true, "Blocking instruction MUST break the tick pipeline");
        ASSERT_TEST(current[0] == nullptr, "CPU MUST be freed after being blocked"); // [추가 검증] CPU 점유 해제 확인

        // Act & Assert 3: 연산 명령어 (OP_COMPUTE) -> TC1
        task.state = TASK_RUNNING; // 임시 복구 (시뮬레이션 진행을 위해)
        current[0] = &task;        // 다시 CPU 0번에 올림
        break_tick = false;

        Instruction inst_compute = {OP_COMPUTE, "", "", 10};
        execute_instruction(0, &task, inst_compute, break_tick);

        ASSERT_TEST(task.remaining_computation == 10, "Remaining computation updated");
        ASSERT_TEST(task.pc == 3, "PC MUST increment");
        ASSERT_TEST(break_tick == true, "COMPUTE MUST break the tick pipeline");

        return true;
    }

    void run_all_unit_tests() {
        cout << "--- Running Deep Unit Tests (Target: sys_*) ---\n";
        int passed = 0, total = 4;
        if (test_sys_fork_edge_cases()) { cout << "[OK] sys_fork : Capacity Limit & Virtual Thread TGID\n"; passed++; }
        if (test_sys_kill_deferred()) { cout << "[OK] sys_kill : Deferred Kill & Wait Queue Exit\n"; passed++; }
        if (test_sys_lock_strict_fifo()) { cout << "[OK] sys_lock/unlock : Strict FIFO Wake-up\n"; passed++; }
        if (test_execute_instruction_pipeline()) { cout << "[OK] execute_inst : Pipeline Break & PC Increment\n"; passed++; }
        cout << "--- Deep Unit Tests Passed: " << passed << "/" << total << " ---\n\n";
    }

#undef ASSERT_TEST
};
#endif

// ==========================================
// [Main / Hardware Layer]
// ==========================================
int main() {
    FASTIO;
    // TDD Verification
#ifdef TEST
    TestKernel test_kernel(100, 100, 2, 5);
    test_kernel.run_all_unit_tests();
#endif

    int maxTime, maxThreads;
    int caseNum = 1;

    while (cin >> maxTime >> maxThreads) {
        if (maxTime == 0 && maxThreads == 0) break;

        int numCPUs, timeSlice, numSemaphores;
        cin >> numCPUs >> timeSlice >> numSemaphores;

        map<string, int> semaphores;
        for (int i = 0; i < numSemaphores; ++i) {
            string name; int val; cin >> name >> val;
            semaphores[name] = val;
        }

        int numCodeBlocks;
        cin >> numCodeBlocks;
        map<string, vector<Instruction>> codeBlocks;
        string firstBlockName;

        for (int i = 0; i < numCodeBlocks; ++i) {
            string blockName; cin >> blockName;
            if (blockName.back() == ':') blockName.pop_back();
            if (i == 0) firstBlockName = blockName;

            vector<Instruction> insts;
            while (true) {
                string token; cin >> token;
                Instruction inst;

                if (token == "end") { inst.opcode = OP_END; insts.push_back(inst); break; }
                else if (token == "compute") { inst.opcode = OP_COMPUTE; cin >> inst.i_operand; }
                else if (token == "yield") { inst.opcode = OP_YIELD; }
                else if (token == "killThread") { inst.opcode = OP_KILL; cin >> inst.s_operand1; }
                else if (token == "lock") { inst.opcode = OP_LOCK; cin >> inst.s_operand1 >> inst.i_operand; }
                else if (token == "unlock") { inst.opcode = OP_UNLOCK; cin >> inst.s_operand1 >> inst.i_operand; }
                else if (token == "loop") { inst.opcode = OP_LOOP; cin >> inst.i_operand; }
                else if (token == "next") { inst.opcode = OP_NEXT; }
                else {
                    // [var] <- forkX [block]
                    string arrow, cmd, block; cin >> arrow >> cmd >> block;
                    inst.s_operand1 = token; // var name
                    inst.s_operand2 = block; // block name
                    inst.opcode = (cmd == "forkR") ? OP_FORK_R : OP_FORK_I;
                }
                insts.push_back(inst);
            }
            codeBlocks[blockName] = insts;
        }

        cout << "Case " << caseNum++ << ":" << endl;
        Kernel kernel(maxTime, maxThreads, numCPUs, timeSlice);
        kernel.start_kernel(semaphores, codeBlocks, firstBlockName);
    }
    return 0;
}