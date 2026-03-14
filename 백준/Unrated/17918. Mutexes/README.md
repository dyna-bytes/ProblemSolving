# [Unrated] Mutexes - 17918 

[문제 링크](https://www.acmicpc.net/problem/17918) 

### 성능 요약

메모리: 405808 KB, 시간: 572 ms

### 분류

분류 없음

### 제출 일자

2026년 3월 15일 01:12:07

### 문제 설명

<p>Anna loves coding multithreaded backend services. In such a service, multiple threads may sometimes need to read and write the same data structures in memory. To ensure all threads have a consistent view of a single datastructure, one can use so-called <em>mutexes</em> to protect access to it.</p>

<p>A mutex is an object that threads can <em>acquire</em> and <em>release</em>. When a mutex is acquired, the mutex cannot be acquired again until it is released -- even by the same thread! If a thread attempts to acquire a mutex it has already acquired, the thread will <em>deadlock</em>, waiting for itself to release the mutex.</p>

<p>Anna has written a program that consists of a number of functions. Each function consists of a list of commands that execute sequentially when the function is called. The commands are each one of:</p>

<ul>
	<li>acquire the mutex named $X$</li>
	<li>release the mutex named $X$</li>
	<li>access a data structure protected by the mutex $X$</li>
	<li>call another function</li>
</ul>

<p>Anna is not sure if she implemented her mutexes correctly, and she wants your help to verify that three properties hold. Assuming a function <code>main</code> is called at the beginning of the program, you should check that:</p>

<ul>
	<li>whenever a data structure protected by a mutex $X$ is to be accessed, the mutex $X$ is currently acquired,</li>
	<li>whenever a mutex is to be acquired, the program has not already acquired it (in order to avoid a deadlock),</li>
	<li>whenever a mutex is to be released, the program is currently holding it.</li>
</ul>

### 입력 

 <p>The first line of the input contains an integer $N$, the number of functions. This is followed by a description of all the $N$ functions.</p>

<p>The description of a function starts with an integer $M$ and a string $X$, meaning that there is a function named $X$ with $M$ commands. This is followed by $M$ lines, each containing a command. The commands will be of the form:</p>

<ul>
	<li><code>acquire X</code> -- the mutex named $X$ is acquired</li>
	<li><code>release X</code> -- the mutex named $X$ is released</li>
	<li><code>access X</code> -- a data structure that must be protected by the mutex $X$ is accessed</li>
	<li><code>call F</code> -- the function called $F$ is called</li>
</ul>

<p>All functions and mutexes have names between $1-10$ characters in length containing only characters <code>a-z</code>. No two functions will have the same name, and there will always be a function called <code>main</code>.</p>

<p>It is guaranteed that there is no infinite recursion: a function will never call itself, either directly or through a chain of other functions.</p>

### 출력 

 <p>If the program is free from errors, output <code>a-ok</code>.</p>

<p>Otherwise, output the first error that occurs during execution. Specifically:</p>

<ul>
	<li>if a data structure is accessed without the correct mutex being acquired, output <code>corruption</code>,</li>
	<li>if a deadlock occurs, output <code>deadlock</code>,</li>
	<li>if a mutex is released without being acquired, output <code>error</code>.</li>
</ul>

<p> </p>

