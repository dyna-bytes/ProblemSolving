# [Platinum IV] Garbage Collection - 22771 

[문제 링크](https://www.acmicpc.net/problem/22771) 

### 성능 요약

메모리: 10160 KB, 시간: 116 ms

### 분류

자료 구조, 분리 집합, 스택

### 제출 일자

2026년 1월 17일 18:52:47

### 문제 설명

<p>Modern programming languages include automatic memory management systems, known as “garbage collection” or “GC”, to simplify the task of programmers.</p>

<p>Many diverse algorithms of GC has been proposed. At the very least, all of them have a common principle: “Do not free memory that is possible to be referred later in the running program. Just free memory that will never be used.” This means, from another point of view, that the core of GC is an algorithm to classify whether a memory block may still be referred in a program (alive memory) or not (dead memory). However, it is not possible, in general, for a garbage collector to determine exactly which blocks are still alive. All garbage collectors hence use some efficient approximation to liveness.</p>

<p>Your friend Prof. George Collins is a researcher of garbage collection. One day, he came up with an new idea for efficient approximation to the liveness classification. Here is his approximation:</p>

<ul>
	<li>A memory block directly pointed from active local variables, which are the variables declared in functions not finished yet, are all considered to be alive.</li>
	<li>If once a pointer in memory block N points another memory block M, life durations of these two blocks are equated. In other words, N is alive if and only if M is alive. This may seem odd, as there can be a situation in which M is referrable from the program but N is not. It is completely true, but for an approximation of liveness, over classification to alive is not a fatal problem. Prof. Collins believes that this approximation gives a significant speed up of garbage collectors.</li>
	<li>Any other memory blocks that cannot be determined to be alive in the two rules above are dead.</li>
</ul>

<p style="text-align: center;"><img alt="" src="https://upload.acmicpc.net/accb4780-69b5-4048-8e26-66cecbc873a8/-/crop/506x284/0,0/-/preview/" style="width: 253px; height: 142px;"></p>

<p style="text-align: center;">Figure 2: An example state with 3 stack frames and 5 objects.</p>

<p style="text-align: center;"><img alt="" src="https://upload.acmicpc.net/accb4780-69b5-4048-8e26-66cecbc873a8/-/crop/506x284/552,0/-/preview/" style="width: 253px; height: 142px;"></p>

<p style="text-align: center;">Figure 3: The object 4 went dead after returning from function g.</p>

<p>Since Prof. Collins is not good at programming, he asked you to write a program to test the performance of his new algorithm. He needs a program which reads a sequence of machine instructions to be executed and logs the number of memory blocks classified as dead by his new algorithm.</p>

<p>The input is a sequence of instructions. For example:</p>

<pre>alloc
call
alloc
alloc
link 1 2
return
return</pre>

<p>There are four kinds of instructions:</p>

<table class="table table-bordered th-center">
	<thead>
		<tr>
			<th>Instruction</th>
			<th>Description</th>
		</tr>
	</thead>
	<tbody>
		<tr>
			<td><code>alloc</code></td>
			<td>Allocates a new memory block and point it from a new local variable in the current function.</td>
		</tr>
		<tr>
			<td><code>link</code> N M</td>
			<td>Points the M-th allocated block from the N-th allocated block (N, M > 0).</td>
		</tr>
		<tr>
			<td><code>call</code></td>
			<td>Calls a function</td>
		</tr>
		<tr>
			<td><code>return</code></td>
			<td>Returns from the current function.</td>
		</tr>
	</tbody>
</table>

<p>Your program should output the number of memory blocks newly classified as dead by Prof. Collins’ method on each <code>return</code> instruction.</p>

<pre>1
2</pre>

<p>In case of the sample input above, on the first <code>return</code> the 3rd memory block goes <code>dead</code> because its depending function is terminated by the <code>return</code> instruction. The 2nd block stays alive since it is pointed by the 1st block, which is still in an active stack frame. Therefore, 1 must be printed. The next <code>return</code> kills the 1st and the 2nd blocks, thus the output is 2.</p>

### 입력 

 <p>Multiple test cases are contained in the input of this problem. Each case begins with a line containing a single integer L (1 ≤ L ≤ 100000), which is the length of the instruction sequence. Then L lines follow. Each line contains one instruction in the form as stated above.</p>

<p>All instruction sequences in the input are valid. That is:</p>

<ul>
	<li>Both arguments of a <code>link</code> instruction are alive memory blocks.</li>
	<li>All but last <code>return</code> instruction have a corresponding <code>call</code> instruction before them.</li>
	<li>The last instruction is always <code>return</code>, which indicates the end of program.</li>
</ul>

<p>The input ends with a line containing just a single 0.</p>

### 출력 

 <p>For every test case, first output a line with the number of the test case as shown in the sample. Then print a line containg the number of new dead blocks on each <code>return</code> instruction in the input sequence.</p>

