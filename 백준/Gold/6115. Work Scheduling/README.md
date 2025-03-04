# [Gold II] Work Scheduling - 6115 

[문제 링크](https://www.acmicpc.net/problem/6115) 

### 성능 요약

메모리: 5136 KB, 시간: 112 ms

### 분류

자료 구조, 그리디 알고리즘, 우선순위 큐, 정렬

### 제출 일자

2025년 3월 4일 20:45:51

### 문제 설명

<p>Farmer John has so very many jobs to do! In order to run the farm efficiently, he must make money on the jobs he does, each one of which takes just one time unit.</p>

<p>His work day starts at time 0 and has 1,000,000,000 time units (!).  He currently can choose from any of N (1 <= N <= 100,000) jobs conveniently numbered 1..N for work to do. It is possible but extremely unlikely that he has time for all N jobs since he can only work on one job during any time unit and the deadlines tend to fall so that he can not perform all the tasks.</p>

<p>Job i has deadline D_i (1 <= D_i <= 1,000,000,000). If he finishes job i by then, he makes a profit of P_i (1 <= P_i <= 1,000,000,000).</p>

<p>What is the maximum total profit that FJ can earn from a given list of jobs and deadlines?  The answer might not fit into a 32-bit integer.</p>

### 입력 

 <ul>
	<li>Line 1: A single integer: N</li>
	<li>Lines 2..N+1: Line i+1 contains two space-separated integers: D_i and P_i</li>
</ul>

<p> </p>

### 출력 

 <ul>
	<li>Line 1: A single number on a line by itself that is the maximum possible profit FJ can earn.</li>
</ul>

<p> </p>

