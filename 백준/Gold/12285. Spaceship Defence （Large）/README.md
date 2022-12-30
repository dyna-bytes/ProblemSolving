# [Gold II] Spaceship Defence (Large) - 12285 

[문제 링크](https://www.acmicpc.net/problem/12285) 

### 성능 요약

메모리: 8392 KB, 시간: 104 ms

### 분류

자료 구조(data_structures), 다익스트라(dijkstra), 그래프 이론(graphs), 해싱(hashing), 해시를 사용한 집합과 맵(hash_set)

### 문제 설명

<p>The enemy has invaded your spaceship, and only superior tactics will allow you to defend it! To travel around your spaceship, your soldiers will use two devices: <em>teleporters</em> and <em>turbolifts</em>.</p>

<p>Teleporters allow your soldiers to move instantly between rooms. Every room contains a teleporter, and rooms are color-coded: if a soldier is in a room with some color, she can use the teleporter in that room to immediately move to any other room with the same color.</p>

<p>Turbolifts allow your soldiers to move between rooms more slowly. A turbolift is like an elevator that moves in many directions. Each turbolift moves from one room to one other room, and it takes a certain amount of time to travel. Notes about turbolifts:</p>

<ul>
	<li>Turbolifts are not two-way: if a turbolift moves soldiers from room a to room b, the same turbolift cannot move soldiers from room b to room a, although there might be another turbolift that does that.</li>
	<li>More than one soldier can use the same turbolift, and they do not interfere with each other in any way.</li>
</ul>

<p><span style="line-height:1.6em">You will be given the locations and destinations of several soldiers. For each soldier, output the minimum amount of time it could take that soldier to travel from his location to his destination.</span></p>

### 입력 

 <p>The first line of the input gives the number of test cases, <strong>T</strong>. <strong>T</strong> test cases follow.</p>

<p>For every test case:</p>

<p>The first line of every test case contains an integer <strong>N</strong>, which is the number of rooms in your spaceship. The rooms are numbered from 1 to <strong>N</strong>. The following <strong>N</strong> lines each contain a string telling the color of the rooms, from room 1 to room <strong>N</strong>. The strings only contain characters a-z (the lower-case English letters) and 0-9 (the number 0 to 9), and the length of each string will be less than or equal to 2.</p>

<p>The next line in the test case is an integer <strong>M</strong>, which indicates the number of turbolifts in your spaceship. The following <strong>M</strong> lines each contain 3 space-separated integers <strong>a</strong><strong><sub>i</sub></strong>, <strong>b</strong><strong><sub>i</sub></strong>, <strong>t</strong><strong><sub>i</sub></strong>, telling us that there is a turbolift that can transport soldiers from room <strong>a</strong><strong><sub>i</sub></strong> to room <strong>b</strong><strong><sub>i</sub></strong> in <strong>t</strong><strong><sub>i</sub></strong> seconds.</p>

<p>The next line in the test case contains an integer <strong>S</strong>, which is the number of soldiers at your command. The following <strong>S</strong> lines each contain two integers: the location and destination of one soldier, <strong>p</strong><strong><sub>j</sub></strong> and <strong>q</strong><strong><sub>j</sub></strong>.</p>

<p>Limits</p>

<ul>
	<li>1 ≤ <strong>S</strong> ≤ 100.</li>
	<li>1 ≤ <strong>a</strong><strong><sub>i</sub></strong><strong>, b</strong><strong><sub>i</sub></strong> ≤ <strong>N</strong>.</li>
	<li>0 ≤ <strong>t</strong><strong><sub>i</sub></strong> ≤ 1000.</li>
	<li>1 ≤ <strong>p</strong><strong><sub>j</sub></strong><strong>, q</strong><strong><sub>j</sub></strong> ≤ <strong>N</strong>.</li>
	<li><strong style="line-height:1.6em">T</strong><span style="line-height:1.6em"> = 1.</span></li>
	<li>1 ≤ <strong>N</strong> ≤ 80000.</li>
	<li>0 ≤ <strong>M</strong> ≤ 3000.</li>
</ul>

### 출력 

 <p>For each test case, output one line containing only the string "Case #x:", where x is the number of the test case (starting from 1). On the next <strong>S</strong> lines, output a single integer: on line <strong>j</strong>, the smallest number of seconds it could take for a soldier to travel from <strong>p</strong><strong><sub>j</sub></strong> to <strong>q</strong><strong><sub>j</sub></strong>. If there is no path from <strong>p</strong><strong><sub>j</sub></strong> to <strong>q</strong><strong><sub>j</sub></strong>, the integer you output should be -1.</p>

