# [Unrated] Asynchronous Exceptions - 11696 

[문제 링크](https://www.acmicpc.net/problem/11696) 

### 성능 요약

메모리: 2328 KB, 시간: 4 ms

### 분류

분류 없음

### 제출 일자

2026년 2월 17일 01:12:22

### 문제 설명

<p>Your job is to simulate the operation on a machine called ACM (Asynchrounous Calculating Machine) to determine how long each program takes to finish their job. This helps detecting unexpected thread behaviors, like race and deadlock.</p>

<p>ACM has many processing units and can run many threads simultaneously. It runs a global scheduler, which maintains all the threads, assigns a thread on each processing unit and manages all semaphores. Each thread has its own thread id and every thread is one of three states: RUNNING, READY, and WAITING. Global scheduler has one thread queue which contains all the threads in READY state.</p>

<h3>explanation of a program</h3>

<p>A program consists of one or more code blocks. Each code block has a list of ACM operations, including the actual computations and thread creation. Each thread runs operations in only one of the given code blocks, and it runs operations from the top of the block to the bottom, unless it receives killThread-signal from other threads.</p>

<h3>explanation of operations</h3>

<p>ACM simulation program simulates 9 operations. Here I describe them all. Please note that word enclosed by [] should have some actual name or value.</p>

<ul>
	<li><strong>compute [clock]</strong> Spend [clock] clocks for computation. When this operation is interrupted after spending T clocks by other threads or the scheduler and is resumed later, it consumes [clock] - T clocks.</li>
	<li><strong>[thread-var] <- forkR [code block]</strong> Generate a native thread running on [code block] and store its id in a thread variable [thread-var]. It can run simultaneously with any threads which are generated in other processing unit. If [thread-var] is used before in the thread, its previous value is overwritten and lost. (This means that we will not be able to refer to the thread although it might run forever.)</li>
	<li><strong>[thread-var] <- forkI [code block]</strong> Generate a virtual thread running on [code block] and store its id in a thread variable [thread-var]. A virtual thread shares some OS resources with its parent thread, so they can’t run simultaneously even there are idle processing units. This restriction is applied to any two threads which are directly or indirectly connected by the parent-child relatinship of forkI. If [thread-var] is used before in the thread, its previous value is overwritten and lost.</li>
	<li><strong>yield</strong> Make the current thread from running state to ready state. The thread goes to the end of the thread queue.</li>
	<li><strong>killThread [thread-var]</strong> Send a kill signal to the [thread-var] thread. [thread-var] guaranteed to be used in either forkR or forkI operations in the same code block before this operation. When a thread receives a kill signal, it immediately cancels its resource requests by lock, changes into ready state if it‘s in block state, and ends its operation when it’s in running state. This operation does not change the semaphore values. If the target thread is already ended, this operation does nothing.</li>
	<li><strong>lock [semaphore name] [amount]</strong> Request [amount] of [semaphore name]. If the value of [semaphore name] is greater or equal to the [amount], it just subtracts the [amount] from the semaphore variable. Otherwise, the operation blocks the current thread until the variable is greater or equal to the [amount]. Once the variable gets greater or equal to the [amount], the thread gets into READY state and goes into the thread queue after subtracting [amount] from the variable. If there are more than one thread requesting for the same semaphore, the thread which locked the semaphore first always gets READY first. So, the other threads won’t get READY even if the semaphore variable meets their demands. If there are more than one thread getting READY, the thread which locked the semaphore earlier goes into the queue first.</li>
	<li><strong>unlock [semaphore name] [amount]</strong> Add [amount] to [semaphore name]. Values of semaphores can be larger than initial values. The thread doesn’t get blocked at all by this operation.</li>
	<li><strong>loop [loop count]</strong> Run the code snippet between loop and corresponding next command for [loop count] times.</li>
	<li><strong>next</strong> This corresponds a loop command in the same code block. The code snippet between loop and next should be run.</li>
	<li><strong>end</strong> End the operation. This command only appears in the end of the code block, and each code block has this operation at the end.</li>
</ul>

<p>Each parameter should either be a name or a digit. A name is an alphabetic string (case-sensitive) and its length is at most 200. Here are some explanations.</p>

<ul>
	<li><strong>[thread-var]</strong> It is a name. It only refers to the id in the same thread. Each thread has its own value even it has the same name.</li>
	<li><strong>[clock]</strong> It is a non-negative integer which is at most 1,000.</li>
	<li><strong>[semaphore-name]</strong> It is a name.</li>
	<li><strong>[amount]</strong> It is a non-negative integer which is at most 1,000.</li>
	<li><strong>[loop count]</strong> It is a non-negative integer which is at most 1,000.</li>
</ul>

<p>Additionally, you may assume following constraints.</p>

<ul>
	<li>Total number of lines that all threads evaluate throughout simulation never exceeds 100,000.</li>
	<li>Size of input file never exceeds 100KB.</li>
</ul>

<h3>explanation of a simulator</h3>

<p>Threads are assigned to CPUs when</p>

<ul>
	<li>a simulation starts. (A thread is assigned to CPU 1. Its code block is the first code block of the input.)</li>
	<li>there are more than one threads that are in ready state which can be assigned to a CPU. (Threads are asssinged in the thread queue order. If there are more than one CPUs that can be assinged to the thread, the smallest CPU is selected.)</li>
	<li>time step is a multiple of time slice. (If the CPU has a thread that is running state, the thread goes to ready state in asscending order of the CPU id. After this, threads are assigned to each CPU in asscending order of the CPU id.)</li>
</ul>

<p>In each step, the simulator does round-robin preemption (when time step is a multiple of time slice), executes operations of each running threads and increments time step. When a compute operation is executed, the thread gets computing time. A thread that has computing time greater than 0 cannot do any operations. After each step, the simulator decrements positive computing time of each running thread.</p>

<p>Operations executed in the same time step is executed in ascending order of the CPU id. In the same time step, a CPU id of an operation is greater or equal to CPU ids of operations which have already been executed.</p>

<p>Time step starts from 0.</p>

### 입력 

 <p>Input consists of multiple testcases.</p>

<p>Each testcase begins with a line that contains two integers separated by a space. They mean the number of time steps of the simulation and the maximum number of threads that ACM is capable, respectively. The next line contains a single integer, which indicates the number of CPUs available. The following line has an integer that means time slice of the scheduler.</p>

<p>Description of semaphores follows. It begins with the number of semaphores which is followed by information of each semaphore, one per line. The information of a semaphore consists of an alphabet string (case-sensitive) and an integer, which specify the name of the semaphore and its initial value, respectively.</p>

<p>Finally code blocks are given. The number of code blocks comes first, and then each code block is described. The first line of the description of each code block is the name of the block (case-sensitive alphabet string), followed by a colon (:). Following lines describe content of the code block. A code block is an array of operations described above, and one operation is written in one line. You may assume that every code block always ends with an ‘end’ operation.</p>

<p>Input terminates with two zeroes separated by a space character.</p>

<p>constraints</p>

<ul>
	<li>Threre is 1 thread queue.</li>
	<li>The id of the n-th created thread is n.</li>
	<li>CPU ids are 1 though the number of CPUs.</li>
	<li>The number of time steps is at most 1,000.</li>
	<li>The maximum number of threads is at most 1,000.</li>
	<li>The number of CPUs is at most 100.</li>
	<li>Time slice is at most 1,000</li>
	<li>The number of semaphores is at most 1,000.</li>
	<li>The number of code blocks is at most 1,000.</li>
</ul>

### 출력 

 <p>For each test case, print its case number on the first line.</p>

<p>If the number of living threads exceeds ACM‘s capacity, put information of all threads which terminated before exceeding the capacity, and then put “<<oops>>”. If not, and if there are one or more threads not finished at the end of the simulation, put information of all threads terminated, and then put “<<loop>>”. Otherwise (i.e. when all threads terminates within the time), just put information of all threads. All quotes are for clarity.</p>

<p>Information of threads must be written in increasing order of thread ID, one per line. Information of a single thread is denoted by two integers, the thread ID and the time it terminated, separated by a single space character.</p>

