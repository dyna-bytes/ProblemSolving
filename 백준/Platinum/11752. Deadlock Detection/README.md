# [Platinum III] Deadlock Detection - 11752 

[문제 링크](https://www.acmicpc.net/problem/11752) 

### 성능 요약

메모리: 7264 KB, 시간: 216 ms

### 분류

이분 탐색

### 제출 일자

2026년 1월 25일 18:16:23

### 문제 설명

<p>You are working on an analysis of a system with multiple processes and some kinds of resource (such as memory pages, DMA channels, and I/O ports). Each kind of resource has a certain number of instances. A process has to acquire resource instances for its execution. The number of required instances of a resource kind depends on a process. A process finishes its execution and terminates eventually after all the resource in need are acquired. These resource instances are released then so that other processes can use them. No process releases instances before its termination. Processes keep trying to acquire resource instances in need, one by one, without taking account of behavior of other processes. Since processes run independently of others, they may sometimes become unable to finish their execution because of deadlock.</p>

<p>A process has to wait when no more resource instances in need are available until some other processes release ones on their termination. Deadlock is a situation in which two or more processes wait for termination of each other, and, regrettably, forever. This happens with the following scenario: One process A acquires the sole instance of resource X, and another process B acquires the sole instance of another resource Y; after that, A tries to acquire an instance of Y, and B tries to acquire an instance of X. As there are no instances of Y other than one acquired by B, A will never acquire Y before B finishes its execution, while B will never acquire X before A finishes. There may be more complicated deadlock situations involving three or more processes.</p>

<p>Your task is, receiving the system’s resource allocation time log (from the system’s start to a certain time), to determine when the system fell into a deadlock-unavoidable state. Deadlock may usually be avoided by an appropriate allocation order, but deadlock-unavoidable states are those in which some resource allocation has already been made and no allocation order from then on can ever avoid deadlock.</p>

<p>Let us consider an example corresponding to Sample Input 1 below. The system has two kinds of resource R<sub>1</sub> and R<sub>2</sub>, and two processes P<sub>1</sub> and P<sub>2</sub>. The system has three instances of R<sub>1</sub> and four instances of R<sub>2</sub>. Process P<sub>1</sub> needs three instances of R<sub>1</sub> and two instances of R<sub>2</sub> to finish its execution, while process P<sub>2</sub> needs a single instance of R<sub>1</sub> and three instances of R<sub>2</sub>. The resource allocation time log is given as follows.</p>

<table class="table table-bordered">
	<thead>
		<tr>
			<th> </th>
			<th> </th>
			<th colspan="2">P<sub>1</sub>'s need</th>
			<th colspan="2">P<sub>2</sub>'s need</th>
			<th colspan="2">available</th>
			<th> </th>
		</tr>
		<tr>
			<th>time</th>
			<th>event</th>
			<th>R<sub>1</sub></th>
			<th>R<sub>2</sub></th>
			<th>R<sub>1</sub></th>
			<th>R<sub>2</sub></th>
			<th>R<sub>1</sub></th>
			<th>R<sub>2</sub></th>
			<th>deadlock</th>
		</tr>
	</thead>
	<tbody>
		<tr>
			<th>0</th>
			<th>start.</th>
			<td>3</td>
			<td>2</td>
			<td>1</td>
			<td>3</td>
			<td>3</td>
			<td>4</td>
			<td> </td>
		</tr>
		<tr>
			<th>1</th>
			<th>P<sub>1</sub> acquired R<sub>1</sub>.</th>
			<td>2</td>
			<td>2</td>
			<td>1</td>
			<td>3</td>
			<td>2</td>
			<td>4</td>
			<td> </td>
		</tr>
		<tr>
			<th>2</th>
			<th>P<sub>2</sub> acquired R<sub>2</sub>.</th>
			<td>2</td>
			<td>2</td>
			<td>1</td>
			<td>2</td>
			<td>2</td>
			<td>3</td>
			<td> </td>
		</tr>
		<tr>
			<th>3</th>
			<th>P<sub>1</sub> acquired R<sub>2</sub>.</th>
			<td>2</td>
			<td>1</td>
			<td>1</td>
			<td>2</td>
			<td>2</td>
			<td>2</td>
			<td> </td>
		</tr>
		<tr>
			<th>4</th>
			<th>P<sub>2</sub> acquired R<sub>1</sub>.</th>
			<td>2</td>
			<td>1</td>
			<td>0</td>
			<td>2</td>
			<td>1</td>
			<td>2</td>
			<td>avoidable by finishing P<sub>2</sub> first</td>
		</tr>
		<tr>
			<th>5</th>
			<th>P<sub>1</sub> acquired R<sub>2</sub>.</th>
			<td>2</td>
			<td>0</td>
			<td>0</td>
			<td>2</td>
			<td>1</td>
			<td>1</td>
			<td>unavoidable</td>
		</tr>
		<tr>
			<th>6</th>
			<th>P<sub>2</sub> acquired R<sub>2</sub>.</th>
			<td>2</td>
			<td>0</td>
			<td>0</td>
			<td>1</td>
			<td>1</td>
			<td>0</td>
			<td> </td>
		</tr>
		<tr>
			<th>7</th>
			<th>P<sub>1</sub> acquired R<sub>1</sub>.</th>
			<td>1</td>
			<td>0</td>
			<td>0</td>
			<td>1</td>
			<td>0</td>
			<td>0</td>
			<td>arisen</td>
		</tr>
	</tbody>
</table>

<p><span style="line-height:1.6em">At time 4, P<sub>2</sub> acquired R<sub>1</sub> and the number of available instances of R<sub>1</sub> became less than P<sub>1</sub>’s need of R<sub>1</sub>. Therefore, it became necessary for P<sub>1</sub> to wait P<sub>2</sub> to terminate and release the instance. However, at time 5, P<sub>1</sub> acquired R<sub>2</sub> necessary for P<sub>2</sub> to finish its execution, and thus it became necessary also for P<sub>2</sub> to wait P<sub>1</sub>; the deadlock became unavoidable at this time.</span></p>

<p><span style="line-height:1.6em">Note that the deadlock was still avoidable at time 4 by finishing P2 first (Sample Input 2).</span></p>

### 입력 

 <p>The input consists of a single test case formatted as follows.</p>

<pre>p r t
l<sub>1</sub> · · · l<sub>r</sub>
n<sub>1,1</sub> · · · n<sub>1,r</sub>
.
.
.
n<sub>p,1</sub> · · · n<sub>p,r</sub>
P<sub>1</sub> R<sub>1</sub>
.
.
.
P<sub>t</sub> R<sub>t</sub></pre>

<p>p is the number of processes, and is an integer between 2 and 300, inclusive. The processes are numbered 1 through p. r is the number of resource kinds, and is an integer between 1 and 300, inclusive. The resource kinds are numbered 1 through r. t is the length of the time log, and is an integer between 1 and 200, 000, inclusive. l<sub>j</sub> (1 ≤ j ≤ r) is the number of initially available instances of the resource kind j, and is an integer between 1 and 100, inclusive. n<sub>i,j</sub> (1 ≤ i ≤ p, 1 ≤ j ≤ r) is the number of resource instances of the resource kind j that the process i needs, and is an integer between 0 and l<sub>j</sub>, inclusive. For every i, at least one of ni,j is non-zero. Each pair of P<sub>k</sub> and R<sub>k</sub> (1 ≤ k ≤ t) is a resource allocation log at time k meaning that process P<sub>k</sub> acquired an instance of resource R<sub>k</sub>.</p>

<p>You may assume that the time log is consistent: no process acquires unnecessary resource instances; no process acquires instances after its termination; and a process does not acquire any instance of a resource kind when no instance is available.</p>

### 출력 

 <p>Print the time when the system fell into a deadlock-unavoidable state. If the system could still avoid deadlock at time t, print −1.</p>

