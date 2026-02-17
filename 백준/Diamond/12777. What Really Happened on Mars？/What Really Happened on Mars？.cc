#include <iostream>
#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)

/* Architecture-specific macros */
#ifndef likely
#define likely(x)		__builtin_expect(!!(x), 1)
#define unlikely(x)		__builtin_expect(!!(x), 0)
#endif

/* POSIX-compatible types */
#ifndef pid_t
typedef int pid_t;
#endif

/* Kernel return codes */
#define EOK				(0)
#define ESYSCALL_EBUSY	(-1)
#define ESYSCALL_PANIC	(-2)

/* Task state bits (Linux kernel style) */
#define __TASK_INACTIVE		0
#define __TASK_READY		1
#define __TASK_RUNNING		2
#define __TASK_BLOCKED		3
#define __TASK_FINISHED		4

enum task_state_t {
	TASK_INACTIVE	= (1 << __TASK_INACTIVE),
	TASK_READY		= (1 << __TASK_READY),
	TASK_RUNNING	= (1 << __TASK_RUNNING),
	TASK_BLOCKED	= (1 << __TASK_BLOCKED),
	TASK_FINISHED	= (1 << __TASK_FINISHED)
};

/* Instruction opcodes */
enum instr_opcode_t {
	OP_COMPUTE = 0,
	OP_LOCK,
	OP_UNLOCK
};

/* Debug macros */
#define KERNEL_DBG 1
#if KERNEL_DBG
#define kprintk(fmt, ...) printf("[%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)
#else
#define kprintk(fmt, ...)
#endif

/* ================================================================
 * [Data Structures - Kernel Objects]
 * ================================================================ */

/* Forward declaration */
struct task_struct;

/* Machine Instruction Format */
struct instr {
	instr_opcode_t opcode;
	int operand;
};

/* Semaphore Object (IPC) */
struct semaphore {
	int id;
	int prio_ceiling;
	task_struct* owner_task;
};

/* Task/Thread Control Block */
struct task_struct {
	/* Identification */
	pid_t pid;

	/* Scheduler state */
	enum task_state_t state;
	int base_prio;
	int curr_prio;

	/* CPU Context */
	unsigned int pc;
	vector<instr> instructions;
	vector<int> held_semaphores;
	set<task_struct*> blocking_tasks;

	/* Lifecycle */
	unsigned int start_time;
	unsigned int finish_time;

	/* Constructors */
	task_struct()
		: pid(0), state(TASK_INACTIVE), base_prio(0), curr_prio(0),
		  pc(0), start_time(0), finish_time(0) {}

	explicit task_struct(pid_t _pid, enum task_state_t _state)
		: pid(_pid), state(_state), base_prio(0), curr_prio(0),
		  pc(0), start_time(0), finish_time(0) {}

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
	unsigned int sys_jiffies;
	unsigned int nr_tasks;
	unsigned int finished_count;

	/* CPU & Scheduling */
	task_struct* current;
	vector<task_struct*> ready_queue;
	vector<task_struct*> wait_queue;

	/* IPC */
	map<int, semaphore>& semaphores;

	/* Task Database */
	vector<task_struct>& tasks;

public:
	kernel(int T, vector<task_struct>& t, map<int, semaphore>& s)
		: sys_jiffies(0), nr_tasks(T), finished_count(0),
		  current(nullptr), tasks(t), semaphores(s) {}

	/* ----- Priority & Ceiling Management ----- */
	int __calc_inherited_prio(task_struct* tsk) {
		int max_prio = tsk->base_prio;
		for (task_struct* blocked: tsk->blocking_tasks)
			max_prio = max(max_prio, __calc_inherited_prio(blocked));
		return max_prio;
	}

	void __update_prio(task_struct* tsk) {
		tsk->curr_prio = __calc_inherited_prio(tsk);
	}

	pair<int, task_struct*> __get_sys_ceiling(void) {
		int max_ceil = -1;
		task_struct* owner = nullptr;
		for (const auto& [id, sem]: semaphores) {
			if (likely(sem.owner_task)) {
				if (sem.prio_ceiling > max_ceil) {
					max_ceil = sem.prio_ceiling;
					owner = sem.owner_task;
				}
			}
		}
		return { max_ceil, owner };
	}

	/* ----- Queue Management ----- */
	void __enqueue_ready(task_struct* tsk) {
		/* Prevent duplicate enqueue of already-ready tasks */
		if (unlikely(tsk->state == TASK_READY)) return;
		tsk->state = TASK_READY;
		ready_queue.push_back(tsk);
	}

	void __enqueue_wait_queue(task_struct* tsk) {
		tsk->state = TASK_BLOCKED;
		wait_queue.push_back(tsk);
	}

	void __schedule(void) {
		if (likely(current)) {
			if (current->state == TASK_RUNNING) {
				/* Preempted task goes to ready queue (__enqueue_ready sets state to READY) */
				__enqueue_ready(current);
			}
			current = nullptr;
		}
		if (unlikely(ready_queue.empty())) return;

		auto best_it = ready_queue.begin();
		for (auto it = ready_queue.begin(); it != ready_queue.end(); ++it) {
			task_struct* tsk = *it;
			task_struct* best = *best_it;
			if (tsk->curr_prio > best->curr_prio)
				best_it = it;
		}

		current = *best_it;
		ready_queue.erase(best_it);
		current->state = TASK_RUNNING;
	}

	/* ----- System Calls (IPC) ----- */
	int do_lock(task_struct* tsk, int sem_id) {
		semaphore& sem = semaphores[sem_id];
		auto [sys_ceil, sys_ceil_owner] = __get_sys_ceiling();

		task_struct* blocker = nullptr;
		if (likely(sem.owner_task)) {
			blocker = sem.owner_task;
		} else if (unlikely(sys_ceil_owner && sys_ceil_owner != tsk)) {
			if (tsk->curr_prio <= sys_ceil)
				blocker = sys_ceil_owner;
		}

		if (unlikely(blocker)) {
			__enqueue_wait_queue(tsk);
			blocker->blocking_tasks.insert(tsk);
			__update_prio(blocker);
			return ESYSCALL_EBUSY;
		}

		sem.owner_task = tsk;
		tsk->held_semaphores.push_back(sem_id);
		return EOK;
	}

	void do_unlock(task_struct* tsk, int sem_id) {
		semaphore& sem = semaphores[sem_id];
		sem.owner_task = nullptr;
		if (likely(!tsk->held_semaphores.empty()))
			tsk->held_semaphores.pop_back();

		for (auto& t: tasks) t.blocking_tasks.clear();
		for (auto& t: tasks) __update_prio(&t);

		for (task_struct* t: wait_queue)
			__enqueue_ready(t);
		wait_queue.clear();
	}

	/* ----- Kernel Main Loop ----- */
	void kernel_main(void) {
		while (likely(finished_count < nr_tasks)) {
			/* Activate tasks at start_time */
			for (auto& t: tasks) {
				if (unlikely(t.state == TASK_INACTIVE && t.start_time <= sys_jiffies)) {
					t.curr_prio = t.base_prio;
					__enqueue_ready(&t);
				}
			}

			__schedule();

			if (unlikely(!current)) {
				sys_jiffies++;
				continue;
			}

			instr& inst = current->instructions[current->pc];

			switch (inst.opcode) {
			case OP_COMPUTE:
				sys_jiffies++;
				current->pc++;
				break;
			case OP_LOCK:
				if (likely(do_lock(current, inst.operand) == EOK))
					current->pc++;
				break;
			case OP_UNLOCK:
				do_unlock(current, inst.operand);
				current->pc++;
				break;
			default:
				break;
			}

			/* Check task completion */
			if (likely(current->state == TASK_RUNNING &&
					   current->pc >= current->instructions.size())) {
				current->state = TASK_FINISHED;
				current->finish_time = sys_jiffies;
				finished_count++;
			}
		}
	}
};

/* ================================================================
 * [Unit Test Framework]
 * ================================================================ */

#define KERNEL_TEST 1
#if KERNEL_TEST

class kernel_test : public kernel {
#define ASSERT_EQ(a, b, msg) \
	if ((a) != (b)) { \
		cerr << "[❌ FAIL] " << msg << " | Expected: " << (b) << ", Got: " << (a) << " (Line: " << __LINE__ << ")" << endl; \
	} else { \
		cout << "[✅ PASS] " << msg << endl; \
	}

#define ASSERT_TRUE(cond, msg) \
	if (!(cond)) { \
		cerr << "[❌ FAIL] " << msg << " (Line: " << __LINE__ << ")" << endl; \
	} else { \
		cout << "[✅ PASS] " << msg << endl; \
	}

public:
	kernel_test(int T, vector<task_struct>& t, map<int, semaphore>& s) : kernel(T, t, s) {}

	void run_all_tests(void) {
		cout << "========== Kernel Unit Tests ==========\n";
		test_enqueue_ready_guards();
		test_schedule_state_transitions();
		test_lock_ceiling_blocking();
		test_priority_inheritance();
		test_unlock_behavior();
		cout << "========== End Unit Tests ==========\n";
	}

private:
	void test_enqueue_ready_guards(void) {
		cout << "\n[Test 1] __enqueue_ready() protection logic\n";
		ready_queue.clear();
		task_struct t1; t1.pid = 1; t1.state = TASK_INACTIVE;

		__enqueue_ready(&t1);
		ASSERT_EQ(1, ready_queue.size(), "INACTIVE task should be enqueued");
		ASSERT_EQ(TASK_READY, t1.state, "Task state should be READY");

		__enqueue_ready(&t1);
		ASSERT_EQ(1, ready_queue.size(), "Duplicate enqueue prevention");

		task_struct t2; t2.pid = 2; t2.state = TASK_RUNNING;
		__enqueue_ready(&t2);
		ASSERT_EQ(2, ready_queue.size(), "RUNNING task can be enqueued (state changes to READY)");
	}

	void test_schedule_state_transitions(void) {
		cout << "\n[Test 2] __schedule() context switch logic\n";
		ready_queue.clear();
		task_struct t1; t1.pid = 1; t1.curr_prio = 5;  t1.state = TASK_RUNNING;
		task_struct t2; t2.pid = 2; t2.curr_prio = 8;  t2.state = TASK_READY;
		task_struct t3; t3.pid = 3; t3.curr_prio = 3;  t3.state = TASK_READY;

		current = &t1;
		ready_queue.push_back(&t2);
		ready_queue.push_back(&t3);

		/* Before __schedule: ready_queue=[t2(prio=8), t3(prio=3)], current=t1(prio=5, RUNNING) */
		/* __schedule: t1(RUNNING)->__enqueue_ready->READY->queue (back), select max prio */
		/* After: current should be t2 (prio=8 > t1=5 > t3=3), queue=[t1, t3] */
		__schedule();

		ASSERT_TRUE(current != nullptr, "Current task should not vanish");
		ASSERT_EQ(2, current->pid, "T2 (highest prio=8) should be scheduled");
		ASSERT_EQ(2, ready_queue.size(), "T1 and T3 should remain in queue");

		/* Test: blocked task eviction */
		task_struct t4; t4.pid = 4; t4.curr_prio = 100; t4.state = TASK_BLOCKED;
		current = &t4;
		__schedule();

		/* BLOCKED task should not enqueue, select max from ready_queue */
		ASSERT_EQ(1, current->pid, "BLOCKED task evicted, T1(prio=5 > T3=3) selected");
		bool found = false;
		for (task_struct* t : ready_queue) if (t->pid == 4) found = true;
		ASSERT_TRUE(!found, "BLOCKED task should not be in ready_queue");
	}

	void test_lock_ceiling_blocking(void) {
		cout << "\n[Test 3] do_lock() PCP ceiling rule\n";
		wait_queue.clear();
		task_struct t_owner; t_owner.pid = 1; t_owner.curr_prio = 5;
		task_struct t_req;   t_req.pid = 2; t_req.curr_prio = 8;

		semaphore s1; s1.id = 0; s1.prio_ceiling = 10; s1.owner_task = &t_owner;
		semaphore s2; s2.id = 1; s2.prio_ceiling = 5;  s2.owner_task = nullptr;

		semaphores.clear();
		semaphores[0] = s1;
		semaphores[1] = s2;

		int ret = do_lock(&t_req, 1);

		ASSERT_EQ(ESYSCALL_EBUSY, ret, "Lock should fail (prio <= ceiling)");
		ASSERT_EQ(TASK_BLOCKED, t_req.state, "Task should be BLOCKED");
		ASSERT_EQ(1, wait_queue.size(), "Task should be in wait_queue");
		ASSERT_TRUE(t_owner.blocking_tasks.count(&t_req) > 0, "Blocking relationship must exist");

		/* PCP Exception Rule: System ceiling owner is exempt from ceiling constraint */
		int self_ret = do_lock(&t_owner, 1);
		ASSERT_EQ(EOK, self_ret, "System ceiling owner is exempt from ceiling block");
	}

	void test_priority_inheritance(void) {
		cout << "\n[Test 4] __calc_inherited_prio() propagation\n";
		task_struct low; low.pid = 1; low.base_prio = 2; low.curr_prio = 2;
		task_struct mid; mid.pid = 2; mid.base_prio = 5; mid.curr_prio = 5;
		task_struct high; high.pid = 3; high.base_prio = 10; high.curr_prio = 10;

		mid.blocking_tasks.insert(&high);
		low.blocking_tasks.insert(&mid);

		__update_prio(&low);
		__update_prio(&mid);

		ASSERT_EQ(10, low.curr_prio, "Low task inherits high prio");
		ASSERT_EQ(10, mid.curr_prio, "Mid task inherits high prio");
	}

	void test_unlock_behavior(void) {
		cout << "\n[Test 5] do_unlock() waiter release\n";
		ready_queue.clear();
		wait_queue.clear();

		/* First, populate tasks vector, then use vector addresses */
		tasks.clear();
		tasks.push_back(task_struct(1, TASK_RUNNING));
		tasks.push_back(task_struct(2, TASK_BLOCKED));

		task_struct* pt_owner = &tasks[0];
		task_struct* pt_wait = &tasks[1];

		pt_owner->base_prio = 2;
		pt_owner->curr_prio = 10;
		pt_wait->base_prio = 10;

		semaphore s1;
		s1.id = 0;
		s1.owner_task = pt_owner;
		pt_owner->held_semaphores.push_back(0);

		semaphores.clear();
		semaphores[0] = s1;

		wait_queue.push_back(pt_wait);
		pt_owner->blocking_tasks.insert(pt_wait);

		do_unlock(pt_owner, 0);

		ASSERT_EQ(nullptr, semaphores[0].owner_task, "Semaphore owner should be NULL");
		ASSERT_EQ(0, wait_queue.size(), "wait_queue should be empty");
		ASSERT_EQ(1, ready_queue.size(), "T2 should move to ready_queue");
		ASSERT_EQ(TASK_READY, ready_queue[0]->state, "T2 state should be READY");
		ASSERT_EQ(2, pt_owner->curr_prio, "T1 prio should revert to base");
	}
};
#undef ASSERT_EQ
#undef ASSERT_TRUE

#endif /* KERNEL_TEST */

/* ================================================================
 * [Main Entry Point]
 * ================================================================ */

int main(void) {
	FASTIO;

#if KERNEL_TEST
	vector<task_struct> dummy_tasks;
	map<int, semaphore> dummy_semaphores;
	kernel_test tester(0, dummy_tasks, dummy_semaphores);
	tester.run_all_tests();
#endif

	int T, R;
	cin >> T >> R;

	vector<task_struct> tasks(T);
	map<int, semaphore> semaphores;

	/* Initialize semaphore table */
	for (int i = 0; i < R; i++) {
		semaphore s;
		s.id = i;
		s.owner_task = nullptr;
		s.prio_ceiling = 0;
		semaphores[i] = s;
	}

	/* Load tasks */
	for (int i = 0; i < T; i++) {
		task_struct& t = tasks[i];
		t.pid = i + 1;
		t.state = TASK_INACTIVE;
		cin >> t.start_time >> t.base_prio;
		t.curr_prio = t.base_prio;

		int inst_size;
		cin >> inst_size;
		t.instructions.reserve(inst_size);

		for (int k = 0; k < inst_size; k++) {
			string in;
			cin >> in;
			char op = in[0];
			int val = stoi(in.substr(1));

			if (op == 'L') {
				val--;		/* 0-indexed */
				t.instructions.push_back({OP_LOCK, val});
				semaphores[val].prio_ceiling = max(semaphores[val].prio_ceiling, t.base_prio);
			} else if (op == 'U') {
				val--;		/* 0-indexed */
				t.instructions.push_back({OP_UNLOCK, val});
			} else if (op == 'C') {
				for (int m = 0; m < val; m++)
					t.instructions.push_back({OP_COMPUTE, 1});
			}
		}
	}

	/* Execute kernel */
	kernel rtos_kernel(T, tasks, semaphores);
	rtos_kernel.kernel_main();

	/* Output results */
	for (int i = 0; i < T; i++) {
		cout << tasks[i].finish_time << endl;
	}

	return 0;
}
