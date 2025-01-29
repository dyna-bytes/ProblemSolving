# [Unrated] Addition (Small) - 12210 

[문제 링크](https://www.acmicpc.net/problem/12210) 

### 성능 요약

메모리: 2040 KB, 시간: 0 ms

### 분류

너비 우선 탐색, 그래프 이론, 그래프 탐색

### 제출 일자

2025년 1월 29일 21:52:17

### 문제 설명

<p>Six years ago, a robot, Bob, with infant's intelligence has been invented by an evil scientist, Alice.</p>

<p>Now the robot is six years old and studies in primary school. Addition is the first operation he learned in math. Due to his strong reasoning ability, he could now conclude a+b=12 from a=2 and b=10.</p>

<p>Alice wanted to test Bob's addition skills. Some equations were given to Bob in form of a=2, b=10, c=4, and Bob has to find out the answers of questions like a+b, a+c, etc.</p>

<p>Alice checked Bob's answers one by one in the test papers, and no mistake has been found so far, but Alice lost the given equations after a cup of coffee poured on them. However she has some of Bob's correct answers, e.g. a+b=12, a+c=6, c+d=5. She wants to continue with the checkable equations, e.g. b+d=11 could be concluded by a+b=12, a+c=6, c+d=5, and thus the question b+d is checkable.</p>

<p>To prevent the artificial intelligence technology from being under the control of Alice, you disguised yourself as her assistant. Now Alice wants you to figure out which of the rest of questions are checkable and their answers.</p>

### 입력 

 <p>The first line of the input gives the number of test cases, <strong>T</strong>. <strong>T</strong> test cases follow.</p>

<p>The first line of each test case contains a single integer <strong>N</strong>: the number of correctly answered questions. Each of the next <strong>N</strong> lines contain one correctly answered question in the form "<strong>x</strong>+<strong>y</strong>=<strong>z</strong>", where <strong>x</strong> and <strong>y</strong> are names of variables and <strong>z</strong> is a decimal integer.</p>

<p>The next line contains a single integer <strong>Q</strong>: the number of remaining questions. Each of the next <strong>Q</strong> lines contain one question in the form "<strong>x</strong>+<strong>y</strong>", where <strong>x</strong> and <strong>y</strong> are names of variables.</p>

<p>Limits</p>

<ul>
	<li>Names of variables are strings of lowercase English letters. Each name contains at most 10 characters.</li>
	<li>-200000 ≤ <strong>z</strong> ≤ 200000</li>
	<li>There is no contradiction in the answered questions and if the answer is checkable, the result is an integer.</li>
	<li><strong style="line-height:1.6em">T</strong><span style="line-height:1.6em"> ≤ 10</span></li>
	<li><strong>N</strong> ≤ 10</li>
	<li><strong>Q</strong> ≤ 10</li>
</ul>

### 출력 

 <p>For each test case, the first line of output contains "Case #<strong>x</strong>:", where <strong>x</strong> is the test case number (starting from 1). For each question in the input that was checkable, output a single line with the answer in the form "<strong>x</strong>+<strong>y</strong>=<strong>z</strong>", where <strong>x</strong> and <strong>y</strong> are names of variables and <strong>z</strong> is a decimal integer. Questions should be listed in the same order as they were given in the input. Please do <strong>NOT</strong> ignore duplicated questions, since Alice would fire you if you pointed any mistake of hers.</p>

