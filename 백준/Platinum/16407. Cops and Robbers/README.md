# [Platinum II] Cops and Robbers - 16407 

[문제 링크](https://www.acmicpc.net/problem/16407) 

### 성능 요약

메모리: 2860 KB, 시간: 16 ms

### 분류

최대 유량(flow), 최대 유량 최소 컷 정리(mfmc)

### 문제 설명

<p>The First Universal Bank of Denview has just been robbed! You want to catch the robbers before they leave the state.</p>

<p>The state of Calirado can be represented by a rectangular n-by-m grid of characters, with the character in each grid cell denoting a terrain type. The robbers begin within the cell marked ‘B’, indicating the Bank of Denview. They will then travel across the state by moving from grid cell to grid cell in the four cardinal directions (left, right, up, down). (Note that the robbers pass only through grid edges, and not corners.) If the robbers manage to leave the state (by crossing any boundary edge of the grid) they will go into hiding, never to be seen again. You must stop this.</p>

<p>To catch the robbers, you can set up barricades. Barricades are placed inside a grid cell, and prevent the robbers from traveling into the cell (from any direction). Each grid square consists of a different type of terrain, with different cost for placing a barricade. You cannot place a barricade on the bank (‘B’) or on any cell containing a dot (‘.’), though the robbers can travel freely through these cells. Every other cell will contain a lowercase English letter, indicating a terrain type.</p>

<p>Find the cheapest way to prevent the robbers from escaping Calirado.</p>

### 입력 

 <p>The first line contains three integers n, m, and c (1 ≤ n, m ≤ 30, 1 ≤ c ≤ 26): the dimensions of the grid representing Calirado, and the number of different terrain types. Then follows m lines of exactly n characters each: the map of Calirado. Each character is either ‘B’, ‘.’, or one of the first c lowercase letters of the English alphabet. Calirado is guaranteed to contain exactly one bank. After the grid, there is a line containing c space-separated integers 1 ≤ c<sub>i</sub> ≤ 100 000, the costs of placing a barricade on a grid cell of each terrain type. c<sub>1</sub> is the cost for terrain type ‘a’, c<sub>2</sub> is the cost for ‘b’, and so forth.</p>

### 출력 

 <p>Print one integer, the minimum total cost of the barricades that you need to place to prevent the robbers from escaping. If there is no way to prevent the robbers from escaping, print -1 instead.</p>

