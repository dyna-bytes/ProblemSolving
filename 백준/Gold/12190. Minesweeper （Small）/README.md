# [Gold V] Minesweeper (Small) - 12190 

[문제 링크](https://www.acmicpc.net/problem/12190) 

### 성능 요약

메모리: 2160 KB, 시간: 8 ms

### 분류

그래프 이론(graphs), 그래프 탐색(graph_traversal)

### 문제 설명

<p>Minesweeper is a computer game that became popular in the 1980s, and is still included in some versions of the Microsoft Windows operating system. This problem has a similar idea, but it does not assume you have played Minesweeper.</p>

<p>In this problem, you are playing a game on a grid of identical cells. The content of each cell is initially hidden. There are M mines hidden in M different cells of the grid. No other cells contain mines. You may click on any cell to reveal it. If the revealed cell contains a mine, then the game is over, and you lose. Otherwise, the revealed cell will contain a digit between 0 and 8, inclusive, which corresponds to the number of neighboring cells that contain mines. Two cells are neighbors if they share a corner or an edge. Additionally, if the revealed cell contains a 0, then all of the neighbors of the revealed cell are automatically revealed as well, recursively. When all the cells that don't contain mines have been revealed, the game ends, and you win.</p>

<p>For example, an initial configuration of the board may look like this ('*' denotes a mine, and 'c' is the first clicked cell):</p>

<pre>*..*...**.
....*.....
..c..*....
........*.
..........
</pre>

<p>There are no mines adjacent to the clicked cell, so when it is revealed, it becomes a 0, and its 8 adjacent cells are revealed as well. This process continues, resulting in the following board:</p>

<pre>*..*...**.
1112*.....
00012*....
00001111*.
00000001..
</pre>

<p>At this point, there are still un-revealed cells that do not contain mines (denoted by '.' characters), so the player has to click again in order to continue the game.</p>

<p>You want to win the game as quickly as possible. You want to find the minimum number of clicks to win the game. Given the size of the board (N x N), output such minimum number of clicks.</p>

### 입력 

 <p>The first line of the input gives the number of test cases, <strong>T</strong>. <strong>T</strong>test cases follow. First line of each test case contains one integer N. N lines strings with length N follows containing '*' and '.', denotes the Minesweeper initial board.</p>

### 출력 

 <p>For each test case, output one line containing "Case #x: y", where x is the test case number (starting from 1) and y is the minimum number of clicks to win.</p>

