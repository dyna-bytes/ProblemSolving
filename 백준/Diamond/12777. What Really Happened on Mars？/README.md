# [Diamond III] What Really Happened on Mars? - 12777 

[문제 링크](https://www.acmicpc.net/problem/12777) 

### 성능 요약

메모리: 3640 KB, 시간: 280 ms

### 분류

애드 혹, 구현, 시뮬레이션

### 제출 일자

2026년 2월 1일 15:36:58

### 문제 설명

<p>Real-time software in the Mars Pathfinder spacecraft suffered from an issue known as priority inversion. One technique to address this issue is to use the Priority Ceiling Protocol.</p>

<p>In this problem, you will simulate the execution of multiple tasks according to this protocol. The tasks share a collection of resources, each of which can be used by only one task at a time. To ensure this, resources must be locked before use and unlocked after use. Each task is defined by a start time, a unique base priority, and a sequence of instructions. Each task also has a current priority, which may change during execution. Instructions come in three types:</p>

<ul>
	<li>compute – perform a computation for one microsecond</li>
	<li>lock k – lock resource k (which takes no processor time)</li>
	<li>unlock k – unlock resource k (which takes no processor time)</li>
</ul>

<p>After locking a resource, a task is said to own the resource until the task unlocks it. A task will unlock only the owned resource it most recently locked, will not lock a resource it already owns, and will complete with no owned resources.</p>

<p>Each resource has a fixed priority ceiling, which is the highest base priority of any task that contains an instruction to lock that resource.</p>

<p>There is a single processor that executes the tasks. When the processor starts, it initializes its clock to zero and then runs an infinite loop with the following steps:</p>

<ul>
	<li>Step 1. Identify running tasks. A task is running if its start time is less than or equal to the current processor clock and not all of its instructions have been executed.</li>
	<li>Step 2. Determine the current priorities of the running tasks and which of the running tasks are blocked. A running task T is blocked if the next instruction in T is to lock resource k and either resource k is already owned or at least one other task owns a resource ℓ whose priority ceiling is greater than or equal to the current priority of T. If T is blocked, it is said to be blocked by every task owning such k or ℓ. The current priority of a task T is the maximum of T’s base priority and the current priorities of all tasks that T blocks.</li>
	<li>Step 3. Execute the next instruction of the non-blocked running task (if any) with the highest current priority. If there was no such task or if a compute instruction was executed, increment the processor clock by one microsecond. If a lock or unlock instruction was executed, do not increment the clock.</li>
</ul>

<p>The Priority Ceiling Protocol defined above has the following properties:</p>

<ul>
	<li>Current priority is defined in terms of current priority and blocking, and blocking is defined in terms of current priority. While this may appear circular, there will always be a unique set of current priorities that satisfy the definitions.</li>
	<li>All tasks will eventually complete.</li>
	<li>There will never be a tie in step 3.</li>
</ul>

### 입력 

 <p>The first line of the input contains two integers t (1 ≤ t ≤ 20), which is the number of tasks, and r (1 ≤ r ≤ 20), which is the number of resources. This is followed by t lines, where the ith of these lines describes task i. The description of a task begins with three integers: the task’s start time s (1 ≤ s ≤ 10 000), its base priority b (1 ≤ b ≤ t), and an integer a (1 ≤ a ≤ 100). A task description is concluded by a sequence of a strings describing the instructions. Each string is a letter (<code>C</code> or <code>L</code> or <code>U</code>) followed by an integer. The string <code>C</code>n (1 ≤ n ≤ 100) indicates a sequence of n compute instructions. The strings <code>L</code>k and <code>U</code>k (1 ≤ k ≤ r) indicate instructions locking and unlocking resource k respectively.</p>

<p>No two tasks have the same base priority.</p>

### 출력 

 <p>For each task, display the time it completes execution, in the same order that the tasks are given in the input.</p>

