#include <iostream>
#include <bits/stdc++.h>

using namespace std;
#define endl '\n'
#define FASTIO ios::sync_with_stdio(0), cin.tie(0)

/* Architecture-specific macros */
#ifndef likely
#define likely(x)		__builtin_expect(!!(x), 1)
#define unlikely(x)		__builtin_expect(!!(x), 0)
#endif

#ifndef pid_t
typedef int pid_t;
#endif

/* Debug Macros */
#define KERNEL_DBG 0
#if KERNEL_DBG
#define kprintk(fmt, ...) printf("[%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)
#define WARN_ON(cond) ((cond) ? (fprintf(stderr, "WARN: %s:%d\n", __func__, __LINE__), 1) : 0)
#else
#define kprintk(fmt, ...)
#define WARN_ON(cond)
#endif

/* ================================================================
 * [Kernel Constants & Return Codes]
 * ================================================================ */
#define MAX_CPUS				100
#define ESYSCALL_EBUSY			(-1)
#define ESYSCALL_PANIC			(-2)
#define EOK						(0)

/* Task State Bits (Linux kernel style) */
#define __TASK_RUNNING			0
#define __TASK_READY			1
#define __TASK_INTERRUPTIBLE	2
#define __TASK_DEAD				3
#define __TASK_ZOMBIE			4

enum task_state_t {
	TASK_RUNNING		= (1 << __TASK_RUNNING),
	TASK_READY			= (1 << __TASK_READY),
	TASK_INTERRUPTIBLE	= (1 << __TASK_INTERRUPTIBLE),
	TASK_DEAD			= (1 << __TASK_DEAD),
	TASK_ZOMBIE			= (1 << __TASK_ZOMBIE)
};

/* Opcode types */
enum instr_opcode_t {
	OP_COMPUTE = 0,
	OP_FORK_R,
	OP_FORK_I,
	OP_YIELD,
	OP_KILL,
	OP_LOCK,
	OP_UNLOCK,
	OP_LOOP,
	OP_NEXT,
	OP_END
};

/* ================================================================
 * [Data Structures - Kernel Objects]
 * ================================================================ */

/* Machine Instruction Format */
struct instr {
	instr_opcode_t opcode;
	string s_operand1;
	string s_operand2;
	int i_operand;
	int jump_pc;		/* For LOOP/NEXT control flow */
};

/* Semaphore Object (IPC) */
struct semaphore {
	int count;			/* Semaphore count */
	deque<int> wait_q;	/* Waiters queue (PIDs) */
};

/* Thread/Task Control Block (Process Descriptor) */
struct task_struct {
	/* Identification */
	pid_t pid;			/* Process ID */
	pid_t tgid;			/* Thread Group ID (for forkI mutual exclusion) */

	/* Scheduler state */
	enum task_state_t state;	/* Current task state */
	int cpu_id;			/* Currently running CPU (-1 if not running) */
	int remaining_ticks;	/* Remaining compute ticks in current slice */

	/* CPU Context (Virtual Machine State) */
	unsigned int pc;	/* Program Counter */
	string code_section;	/* Code section name */
	map<string, int> regs;	/* Register file (local variables) */
	vector<int> loop_stack;	/* Nested loop iteration counters */

	/* IPC state (Semaphore wait) */
	string waiting_sem;
	int wait_amount;

	/* Lifecycle */
	unsigned int exit_time;	/* Time of process termination */
	bool deferred_kill;		/* Deferred termination flag */

	/* Constructors */
	task_struct()
		: pid(0), tgid(0), state(TASK_RUNNING), cpu_id(-1),
		  remaining_ticks(0), pc(0), wait_amount(0), exit_time(0), deferred_kill(false) {}

	explicit task_struct(pid_t _pid, pid_t _tgid, enum task_state_t _state)
		: pid(_pid), tgid(_tgid), state(_state), cpu_id(-1),
		  remaining_ticks(0), pc(0), wait_amount(0), exit_time(0), deferred_kill(false) {}

	bool operator==(const task_struct& other) const {
		return this->pid == other.pid;
	}
};

/* ================================================================
 * [Kernel Subsystem]
 * ================================================================ */

class kernel {
protected:
	/* System Configuration */
	unsigned int sys_jiffies;		/* System timer (jiffies) */
	unsigned int max_jiffies;		/* Maximum simulation time */
	int max_nr_tasks;				/* Task limit */
	int nr_cpus;					/* Number of CPUs */
	unsigned int time_slice;		/* Time slice per task (RR scheduling) */

	/* Memory Management */
	map<string, vector<instr>> text_segments;	/* Code sections */
	map<string, semaphore> sem_table;			/* Semaphore objects */

	/* Process/Task Management */
	deque<task_struct*> runq;		/* Global run queue */
	task_struct* current[MAX_CPUS];	/* Per-CPU current task pointer */
	map<pid_t, task_struct> task_db;	/* Task database (all processes) */

	pid_t next_pid;					/* PID allocator */
	bool kernel_panic;				/* Panic flag */

public:
	kernel(int max_time, int max_threads, int ncpus, int tslice)
		: sys_jiffies(0), max_jiffies(max_time), max_nr_tasks(max_threads),
		  nr_cpus(ncpus), time_slice(tslice), next_pid(1), kernel_panic(false) {
		for (int i = 0; i < MAX_CPUS; i++) {
			current[i] = nullptr;
		}
	}

	/* ================================================================
	 * [System Call Interface] - Called by instruction interpreter
	 * ================================================================ */

	/* do_fork - Process/Thread creation syscall */
	int do_fork(task_struct *parent, const string &var_name,
			   const string &block_name, bool is_virtual) {
		/* Count living processes */
		int nr_living = 0;
		for (auto& [_pid, t] : task_db) {
			if (t.state != TASK_DEAD) nr_living++;
		}

		if (unlikely(nr_living >= max_nr_tasks))
			return ESYSCALL_EBUSY;

		task_struct newtask(next_pid++, 0, TASK_READY);
		newtask.tgid = is_virtual ? parent->tgid : newtask.pid;
		newtask.pc = 0;
		newtask.cpu_id = -1;
		newtask.code_section = block_name;
		newtask.remaining_ticks = 0;
		newtask.wait_amount = 0;

		task_db[newtask.pid] = newtask;
		runq.push_back(&task_db[newtask.pid]);
		parent->regs[var_name] = newtask.pid;

		return EOK;
	}

	/* do_lock - Semaphore P (acquire) operation */
	void do_lock(task_struct *task, const string &sem_name, int amount) {
		semaphore &sem = sem_table[sem_name];

		if (sem.count >= amount) {
			sem.count -= amount;
		} else {
			task->state = TASK_INTERRUPTIBLE;
			task->waiting_sem = sem_name;
			task->wait_amount = amount;
			current[task->cpu_id] = nullptr;
			sem.wait_q.push_back(task->pid);
		}
	}

	/* do_unlock - Semaphore V (release) operation */
	void do_unlock(task_struct *task, const string &sem_name, int amount) {
		semaphore &sem = sem_table[sem_name];

		if (task->state == TASK_INTERRUPTIBLE) {
			auto it = find(sem.wait_q.begin(), sem.wait_q.end(), task->pid);
			if (it != sem.wait_q.end())
				sem.wait_q.erase(it);
		}

		sem.count += amount;

		/* Wake-up waiters in FIFO order */
		while (!sem.wait_q.empty()) {
			pid_t waiter_pid = sem.wait_q.front();
			task_struct *waiter = &task_db[waiter_pid];

			if (sem.count < waiter->wait_amount)
				break;

			sem.count -= waiter->wait_amount;
			waiter->wait_amount = 0;
			waiter->waiting_sem = "";
			waiter->state = TASK_READY;
			runq.push_back(waiter);
			sem.wait_q.pop_front();
		}
	}

	/* do_kill - Send SIGKILL to target process */
	void do_kill(task_struct *sender, const string &target_var) {
		auto it = sender->regs.find(target_var);
		if (it == sender->regs.end())
			return;

		pid_t target_pid = it->second;
		auto task_it = task_db.find(target_pid);
		if (task_it == task_db.end())
			return;

		task_struct *target = &task_it->second;

		if (target->state == TASK_RUNNING) {
			current[target->cpu_id] = nullptr;
			target->state = TASK_DEAD;
			target->exit_time = sys_jiffies;
		} else if (target->state == TASK_READY) {
			target->deferred_kill = true;
		} else if (target->state == TASK_INTERRUPTIBLE) {
			semaphore &sem = sem_table[target->waiting_sem];
			auto w_it = find(sem.wait_q.begin(), sem.wait_q.end(), target->pid);
			if (w_it != sem.wait_q.end())
				sem.wait_q.erase(w_it);

			target->state = TASK_READY;
			target->waiting_sem = "";
			runq.push_back(target);
			target->deferred_kill = true;
		}
	}

	/* do_yield - Relinquish CPU and go to ready queue */
	void do_yield(task_struct *task) {
		current[task->cpu_id] = nullptr;
		task->state = TASK_READY;
		task->cpu_id = -1;
		runq.push_back(task);
	}

	/* ================================================================
	 * [Core Kernel Logic] - Scheduler & Dispatcher
	 * ================================================================ */

	/* tick_handler - Timer interrupt handler (called each tick) */
	void tick_handler(void) {
		/* Round-robin preemption on time slice expiry */
		if (sys_jiffies % time_slice == 0) {
			for (int cpu = 0; cpu < nr_cpus; ++cpu) {
				task_struct *task = current[cpu];
				if (!task) continue;

				task->state = TASK_READY;
				task->cpu_id = -1;
				runq.push_back(task);
				current[cpu] = nullptr;
			}
		}
	}

	/* pick_next_task - Dispatcher: select next task for CPU */
	task_struct* pick_next_task(int cpu) {
		for (auto it = runq.begin(); it != runq.end(); ++it) {
			/* Mutual exclusion check: forkI virtual threads */
			if (is_tgid_running((*it)->tgid))
				continue;

			task_struct *task = *it;
			runq.erase(it);

			task->state = TASK_RUNNING;
			task->cpu_id = cpu;
			current[cpu] = task;
			return task;
		}
		return nullptr;
	}

	/* __finish_task_unlocked - Finalize terminated task */
	bool __finish_task_unlocked(int cpu, task_struct *task) {
		if (task && task->deferred_kill) {
			task->state = TASK_DEAD;
			task->exit_time = sys_jiffies;
			current[cpu] = nullptr;
			return true;
		}
		return false;
	}

	/* execute_instr - Single instruction executor (zero-time or blocking) */
	int execute_instr(int cpu, task_struct *task, instr &inst, bool &should_break) {
		int ret = EOK;

		switch (inst.opcode) {
		case OP_COMPUTE:
			task->remaining_ticks = inst.i_operand;
			task->pc++;
			should_break = true;
			break;

		case OP_YIELD:
			do_yield(task);
			task->pc++;
			should_break = true;
			break;

		case OP_LOCK:
			do_lock(task, inst.s_operand1, inst.i_operand);
			task->pc++;
			if (task->state == TASK_INTERRUPTIBLE) {
				should_break = true;
			}
			break;

		case OP_UNLOCK:
			do_unlock(task, inst.s_operand1, inst.i_operand);
			task->pc++;
			break;

		case OP_END:
			/* Release all held semaphores on exit */
			for (auto& [sem_name, sem] : sem_table) {
				auto it = find(sem.wait_q.begin(), sem.wait_q.end(), task->pid);
				if (it != sem.wait_q.end())
					sem.wait_q.erase(it);
			}
			task->state = TASK_DEAD;
			task->exit_time = sys_jiffies;
			current[cpu] = nullptr;
			should_break = true;
			break;

		case OP_LOOP:
			if (inst.i_operand == 0) {
				task->pc = inst.jump_pc + 1;
			} else {
				task->loop_stack.push_back(inst.i_operand);
				task->pc++;
			}
			break;

		case OP_NEXT:
			{
				int &iter = task->loop_stack.back();
				iter--;
				if (iter > 0) {
					task->pc = inst.jump_pc + 1;
				} else {
					task->loop_stack.pop_back();
					task->pc++;
				}
			}
			break;

		case OP_FORK_R:
			ret = do_fork(task, inst.s_operand1, inst.s_operand2, false);
			if (ret) return ret;
			task->pc++;
			break;

		case OP_FORK_I:
			ret = do_fork(task, inst.s_operand1, inst.s_operand2, true);
			if (ret) return ret;
			task->pc++;
			break;

		case OP_KILL:
			do_kill(task, inst.s_operand1);
			task->pc++;
			break;
		}

		return ret;
	}

	/* run_per_cpu - Per-CPU run loop */
	int run_per_cpu(int cpu) {
		int ret = EOK;

		while (true) {
			task_struct *task = current[cpu];

			/* 1. CPU idle: schedule next task */
			if (!task) {
				task = pick_next_task(cpu);
				if (!task) break;
			}

			/* 2. Check deferred kill */
			if (__finish_task_unlocked(cpu, task)) {
				continue;
			}

			/* 3. Skip instruction if still computing */
			if (task->remaining_ticks > 0) {
				break;
			}

			vector<instr> &text = text_segments[task->code_section];
			bool should_break = false;

			/* 4. Instruction pipeline (zero-time chain execution) */
			while (!should_break && task->state == TASK_RUNNING) {
				instr &inst = text[task->pc];

				ret = execute_instr(cpu, task, inst, should_break);
				if (ret) return ret;
			}

			/* 5. Exit loop if CPU still occupied */
			if (current[cpu] != nullptr) {
				break;
			}
		}

		return ret;
	}

	/* __do_schedule - Main scheduler for all CPUs */
	int __do_schedule(void) {
		int ret = EOK;

		for (int cpu = 0; cpu < nr_cpus; ++cpu) {
			ret = run_per_cpu(cpu);
			if (ret) return ret;
		}

		/* 6. Decrement compute ticks for running tasks */
		for (int cpu = 0; cpu < nr_cpus; ++cpu) {
			task_struct *task = current[cpu];
			if (task && task->remaining_ticks > 0) {
				task->remaining_ticks--;
			}
		}

		return ret;
	}

	/* is_tgid_running - Check if any task in tgid is running */
	bool is_tgid_running(pid_t tgid) {
		for (int cpu = 0; cpu < nr_cpus; ++cpu) {
			if (!current[cpu]) continue;
			if (current[cpu]->tgid == tgid)
				return true;
		}
		return false;
	}

	/* ================================================================
	 * [Kernel Boot & Main Loop]
	 * ================================================================ */

	/* kernel_main - System initialization and main loop */
	void kernel_main(map<string, int> &init_sems,
					 map<string, vector<instr>> &code_sections,
					 const string &init_section) {
		int ret = EOK;

		/* 1. Initialize kernel memory */
		sem_table.clear();
		for (auto& [sem_name, val] : init_sems) {
			sem_table[sem_name] = {val, {}};
		}
		text_segments = code_sections;

		/* 2. Link LOOP/NEXT pairs in code sections */
		for (auto& [section_name, instructions] : text_segments) {
			vector<int> loop_st;
			for (size_t pc = 0; pc < instructions.size(); ++pc) {
				if (instructions[pc].opcode == OP_LOOP) {
					loop_st.push_back(pc);
				} else if (instructions[pc].opcode == OP_NEXT) {
					int loop_pc = loop_st.back();
					loop_st.pop_back();

					instructions[loop_pc].jump_pc = pc;
					instructions[pc].jump_pc = loop_pc;
				}
			}
		}

		/* 3. Create init process (PID 1 - init task) */
		task_struct init_proc(next_pid++, 1, TASK_READY);
		init_proc.pc = 0;
		init_proc.cpu_id = -1;
		init_proc.code_section = init_section;
		init_proc.remaining_ticks = 0;
		init_proc.wait_amount = 0;

		task_db[init_proc.pid] = init_proc;
		runq.push_back(&task_db[init_proc.pid]);

		/* 4. Main event loop - system runs until max_jiffies or all tasks exit */
		while (sys_jiffies <= max_jiffies) {
			/* A. Timer interrupt (RR preemption) */
			tick_handler();

			/* B. Scheduler and instruction execution */
			ret = __do_schedule();
			if (unlikely(ret)) {
				kernel_panic = true;
				break;
			}

			/* C. Advance system clock */
			sys_jiffies++;
		}

		/* 5. Shutdown and report */
		print_accounting();
	}

	/* print_accounting - Terminate and print results */
	void print_accounting(void) {
		bool has_runnable = false;

		for (auto& [_pid, task] : task_db) {
			if (task.state != TASK_DEAD) {
				has_runnable = true;
				break;
			}
		}

		/* Print exit times of dead tasks */
		for (auto& [_pid, task] : task_db) {
			if (task.state == TASK_DEAD) {
				cout << task.pid << " " << task.exit_time << endl;
			}
		}

		/* Report final status */
		if (kernel_panic) {
			cout << "<<oops>>" << endl;
		} else if (has_runnable) {
			cout << "<<loop>>" << endl;
		}
	}
};

/* ================================================================
 * [Unit Testing Framework]
 * ================================================================ */

#define KERNEL_TEST 0
#if KERNEL_TEST

class kernel_test : public kernel {
public:
	kernel_test(int max_t, int max_th, int ncpu, int tslice)
		: kernel(max_t, max_th, ncpu, tslice) {}

	#define ASSERT_EQ(a, b, msg) \
		if ((a) != (b)) { \
			fprintf(stderr, "[FAIL] %s:%d %s (expected %d, got %d)\n", \
				__func__, __LINE__, msg, b, a); \
			return false; \
		}

	#define ASSERT_TRUE(cond, msg) \
		if (!(cond)) { \
			fprintf(stderr, "[FAIL] %s:%d %s\n", __func__, __LINE__, msg); \
			return false; \
		}

	/* Reset kernel state for unit test */
	void test_reset(int mt, int mth, int ncpu, int ts) {
		max_jiffies = mt;
		max_nr_tasks = mth;
		nr_cpus = ncpu;
		time_slice = ts;

		sys_jiffies = 0;
		next_pid = 1;
		kernel_panic = false;

		text_segments.clear();
		sem_table.clear();
		task_db.clear();
		runq.clear();

		for (int i = 0; i < MAX_CPUS; i++)
			current[i] = nullptr;
	}

	/* UT1: do_fork() - capacity and virtual thread TGID */
	bool test_do_fork_tgid_and_capacity(void) {
		test_reset(10, 2, 1, 5);

		/* Setup parent task */
		task_struct parent(next_pid++, 1, TASK_RUNNING);
		task_db[parent.pid] = parent;

		/* Act 1: Create virtual thread */
		int ret1 = do_fork(&task_db[parent.pid], "child1", "blockB", true);

		ASSERT_EQ(ret1, EOK, "First fork should succeed");
		ASSERT_EQ(task_db[parent.pid].regs["child1"], 2, "Child PID saved in parent's regs");
		ASSERT_EQ(task_db[2].tgid, parent.tgid, "Virtual thread inherits parent TGID");

		/* Act 2: Create native thread (should fail - capacity) */
		int ret2 = do_fork(&task_db[parent.pid], "child2", "blockC", false);

		ASSERT_EQ(ret2, ESYSCALL_EBUSY, "Second fork fails on capacity");
		ASSERT_TRUE(task_db.size() == 2, "No extra task created");

		return true;
	}

	/* UT2: do_kill() - deferred kill on READY state */
	bool test_do_kill_deferred_ready(void) {
		test_reset(10, 10, 1, 5);

		/* Setup tasks */
		task_db[1] = task_struct(1, 1, TASK_READY);
		task_db[2] = task_struct(2, 2, TASK_INTERRUPTIBLE);
		task_db[2].waiting_sem = "sem1";

		sem_table["sem1"] = {0, {2}};

		/* Setup killer */
		task_db[9] = task_struct(9, 9, TASK_RUNNING);
		task_db[9].regs["target1"] = 1;
		task_db[9].regs["target2"] = 2;

		/* Act 1: Kill READY task */
		do_kill(&task_db[9], "target1");

		ASSERT_TRUE(task_db[1].state == TASK_READY, "READY task not instantly killed");
		ASSERT_TRUE(task_db[1].deferred_kill, "READY task marked for deferred kill");

		/* Act 2: Kill INTERRUPTIBLE task */
		do_kill(&task_db[9], "target2");

		ASSERT_TRUE(sem_table["sem1"].wait_q.empty(), "Task removed from sem wait_q");
		ASSERT_TRUE(task_db[2].waiting_sem == "", "Waiting sem cleared");
		ASSERT_EQ(task_db[2].state, TASK_READY, "Blocked task becomes READY");
		ASSERT_TRUE(task_db[2].deferred_kill, "Blocked task marked for deferred kill");

		return true;
	}

	/* UT3: do_lock/do_unlock - strict FIFO ordering */
	bool test_do_lock_strict_fifo(void) {
		test_reset(10, 10, 1, 5);

		sem_table["sem1"] = {1, {}};

		task_db[1] = task_struct(1, 1, TASK_RUNNING);
		task_db[1].cpu_id = 0;
		current[0] = &task_db[1];

		task_db[2] = task_struct(2, 2, TASK_RUNNING);
		task_db[2].cpu_id = 1;
		current[1] = &task_db[2];

		task_db[3] = task_struct(3, 3, TASK_RUNNING);

		/* Act 1: Task 1 tries to acquire 2 units (fails, blocks) */
		do_lock(&task_db[1], "sem1", 2);
		ASSERT_EQ(task_db[1].state, TASK_INTERRUPTIBLE, "Task 1 blocked");

		/* Act 2: Task 2 tries to acquire 1 unit (succeeds) */
		do_lock(&task_db[2], "sem1", 1);
		ASSERT_EQ(task_db[2].state, TASK_RUNNING, "Task 2 succeeds");
		ASSERT_EQ(sem_table["sem1"].count, 0, "Sem value is 0");

		/* Act 3: Task 3 releases 1 unit */
		do_unlock(&task_db[3], "sem1", 1);

		/* Assert: Task 1 still blocked (needs 2, only 1 available - FIFO) */
		ASSERT_EQ(sem_table["sem1"].count, 1, "Sem value is 1");
		ASSERT_EQ(task_db[1].state, TASK_INTERRUPTIBLE, "Task 1 still blocked (FIFO)");
		ASSERT_TRUE(sem_table["sem1"].wait_q.size() == 1, "Task 1 in wait_q");

		return true;
	}

	/* UT4: execute_instr() - zero-time pipeline and PC increment on lock */
	bool test_execute_instr_pipeline(void) {
		test_reset(10, 10, 1, 5);

		task_struct task(1, 1, TASK_RUNNING);
		task.cpu_id = 0;
		task.pc = 0;
		current[0] = &task;
		task_db[1] = task;

		sem_table["sem1"] = {0, {}};

		/* Act 1: Execute UNLOCK (zero-time) */
		bool brk = false;
		instr inst_unlock = {OP_UNLOCK, "sem1", "", 1, 0};
		execute_instr(0, &task_db[1], inst_unlock, brk);

		ASSERT_EQ(task_db[1].pc, 1, "PC incremented after UNLOCK");
		ASSERT_TRUE(brk == false, "Zero-time instr doesn't break pipeline");
		ASSERT_EQ(sem_table["sem1"].count, 1, "UNLOCK executed");

		/* Act 2: Execute LOCK (blocking) */
		brk = false;
		instr inst_lock = {OP_LOCK, "sem1", "", 5, 0};
		execute_instr(0, &task_db[1], inst_lock, brk);

		ASSERT_EQ(task_db[1].state, TASK_INTERRUPTIBLE, "Task blocked");
		ASSERT_EQ(task_db[1].pc, 2, "PC incremented EVEN WHEN BLOCKED!");
		ASSERT_TRUE(brk == true, "Blocking instr breaks pipeline");
		ASSERT_TRUE(current[0] == nullptr, "CPU freed");

		return true;
	}

	void run_all_tests(void) {
		int passed = 0, total = 4;
		printf("=== Kernel Unit Tests ===\n");

		if (test_do_fork_tgid_and_capacity())
			{ printf("[OK] do_fork: TGID inheritance & capacity\n"); passed++; }
		if (test_do_kill_deferred_ready())
			{ printf("[OK] do_kill: deferred kill & FIFO\n"); passed++; }
		if (test_do_lock_strict_fifo())
			{ printf("[OK] do_lock/unlock: strict FIFO\n"); passed++; }
		if (test_execute_instr_pipeline())
			{ printf("[OK] execute_instr: pipeline & PC\n"); passed++; }

		printf("=== Test Results: %d/%d passed ===\n\n", passed, total);
	}

	#undef ASSERT_EQ
	#undef ASSERT_TRUE
};

#endif  /* KERNEL_TEST */

/* ================================================================
 * [Hardware Layer - Main]
 * ================================================================ */

int main(void) {
	FASTIO;

#if KERNEL_TEST
	kernel_test test_kern(100, 100, 2, 5);
	test_kern.run_all_tests();
#endif

	int max_t, max_th;
	int case_no = 1;

	while (cin >> max_t >> max_th) {
		if (unlikely(max_t == 0 && max_th == 0))
			break;

		int ncpu, tslice, nsem;
		cin >> ncpu >> tslice >> nsem;

		map<string, int> sems;
		for (int i = 0; i < nsem; ++i) {
			string sem_name;
			int val;
			cin >> sem_name >> val;
			sems[sem_name] = val;
		}

		int nblocks;
		cin >> nblocks;

		map<string, vector<instr>> code_blocks;
		string first_block;

		for (int i = 0; i < nblocks; ++i) {
			string block_name;
			cin >> block_name;

			if (block_name.back() == ':')
				block_name.pop_back();

			if (i == 0)
				first_block = block_name;

			vector<instr> instructions;

			while (true) {
				string token;
				cin >> token;

				if (token == "end") {
					instr inst = {OP_END, "", "", 0, 0};
					instructions.push_back(inst);
					break;
				}

				instr inst = {OP_END, "", "", 0, 0};

				if (token == "compute") {
					inst.opcode = OP_COMPUTE;
					cin >> inst.i_operand;
				}
				else if (token == "yield") {
					inst.opcode = OP_YIELD;
				}
				else if (token == "killThread") {
					inst.opcode = OP_KILL;
					cin >> inst.s_operand1;
				}
				else if (token == "lock") {
					inst.opcode = OP_LOCK;
					cin >> inst.s_operand1 >> inst.i_operand;
				}
				else if (token == "unlock") {
					inst.opcode = OP_UNLOCK;
					cin >> inst.s_operand1 >> inst.i_operand;
				}
				else if (token == "loop") {
					inst.opcode = OP_LOOP;
					cin >> inst.i_operand;
				}
				else if (token == "next") {
					inst.opcode = OP_NEXT;
				}
				else {
					/* [var] <- forkX [block] */
					string arrow, cmd, block;
					cin >> arrow >> cmd >> block;

					inst.s_operand1 = token;  /* var name */
					inst.s_operand2 = block;  /* block name */
					inst.opcode = (cmd == "forkR") ? OP_FORK_R : OP_FORK_I;
				}

				instructions.push_back(inst);
			}

			code_blocks[block_name] = instructions;
		}

		cout << "Case " << case_no++ << ":" << endl;

		kernel kern(max_t, max_th, ncpu, tslice);
		kern.kernel_main(sems, code_blocks, first_block);
	}

	return 0;
}