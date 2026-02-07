# [Platinum I] Deadlock Detection - 11042 

[문제 링크](https://www.acmicpc.net/problem/11042) 

### 성능 요약

메모리: 2308 KB, 시간: 80 ms

### 분류

분류 없음

### 제출 일자

2026년 2월 8일 00:57:28

### 문제 설명

<p>In concurrent processing environments, a deadlock is an undesirable situation where two or more threads are mutually waiting for others to finish using some resources and cannot proceed further. Your task is to detect whether there is any possibility of deadlocks when multiple threads try to execute a given instruction sequence concurrently.</p>

<p>The instruction sequence consists of characters 'u' or digits from '0' to '9', and each of them represents one instruction. 10 threads are trying to execute the same single instruction sequence. Each thread starts its execution from the beginning of the sequence and continues in the given order, until all the instructions are executed.</p>

<p>There are 10 shared resources called locks from L0 to L9. A digit k is the instruction for acquiring the lock Lk. After one of the threads acquires a lock Lk, it is kept by the thread until it is released by the instruction 'u'. While a lock is kept, none of the threads, including one already acquired it, cannot newly acquire the same lock Lk.</p>

<p>Precisely speaking, the following steps are repeated until all threads finish.</p>

<ol>
	<li>One thread that has not finished yet is chosen arbitrarily.</li>
	<li>The chosen thread tries to execute the next instruction that is not executed yet.
	<ul>
		<li>If the next instruction is a digit k and the lock Lk is not kept by any thread, the thread executes the instruction k and acquires Lk.</li>
		<li>If the next instruction is a digit k and the lock Lk is already kept by some thread, the instruction k is not executed.</li>
		<li>If the next instruction is 'u', the instruction is executed and all the locks currently kept by the thread are released.</li>
	</ul>
	</li>
</ol>

<p>After executing several steps, sometimes, it falls into the situation that the next instructions of all unfinished threads are for acquiring already kept locks. Once such a situation happens, no instruction will ever be executed no matter which thread is chosen. This situation is called a deadlock.</p>

<p>There are instruction sequences for which threads can never reach a deadlock regardless of the execution order. Such instruction sequences are called safe. Otherwise, in other words, if there exists one or more execution orders that lead to a deadlock, the execution sequence is called unsafe. Your task is to write a program that tells whether the given instruction sequence is safe or unsafe.</p>

### 입력 

 <p>The input consists of at most 50 datasets, each in the following format.</p>

<pre>n
s</pre>

<p>n is the length of the instruction sequence and s is a string representing the sequence. n is a positive integer not exceeding 10,000. Each character of s is either a digit ('0' to '9') or 'u', and s always ends with 'u'.</p>

<p>The end of the input is indicated by a line with a zero.</p>

### 출력 

 <p>For each dataset, if the given instruction sequence is safe, then print "SAFE" in a line. If it is unsafe, then print "UNSAFE" in a line.</p>

