# [Gold IV] Bad Horse (Small1) - 12082 

[문제 링크](https://www.acmicpc.net/problem/12082) 

### 성능 요약

메모리: 2036 KB, 시간: 0 ms

### 분류

너비 우선 탐색(bfs), 이분 그래프(bipartite_graph), 자료 구조(data_structures), 깊이 우선 탐색(dfs), 그래프 이론(graphs), 그래프 탐색(graph_traversal), 해시를 사용한 집합과 맵(hash_set), 문자열(string)

### 문제 설명

<p>As the leader of the Evil League of Evil, Bad Horse has a lot of problems to deal with. Most recently, there have been far too many arguments and far too much backstabbing in the League, so much so that Bad Horse has decided to split the league into two departments in order to separate troublesome members. Being the Thoroughbred of Sin, Bad Horse isn't about to spend his valuable time figuring out how to split the League members by himself. That what he's got you -- his loyal henchman -- for.</p>

### 입력 

 <p>The first line of the input gives the number of test cases, <strong>T</strong>.  <strong>T</strong> test cases follow. Each test case starts with a positive integer <strong>M</strong> on a line by itself -- the number of troublesome pairs of League members. The next <strong>M</strong> lines each contain a pair of names, separated by a single space.</p>

<h3>Limits</h3>

<ul>
	<li>1 ≤ <strong>T</strong> ≤ 100.</li>
	<li>Each member name will consist of only letters and the underscore character.</li>
	<li>Names are case-sensitive.</li>
	<li>No pair will appear more than once in the same test case.</li>
	<li>Each pair will contain two distinct League members.</li>
	<li>1 ≤ <strong>M</strong> ≤ 10.</li>
</ul>

### 출력 

 <p>For each test case, output one line containing "Case #x: y", where x is the case number (starting from 1) and y is either "Yes" or "No", depending on whether the League members mentioned in the input can be split into two groups with neither of the groups containing a troublesome pair.</p>

