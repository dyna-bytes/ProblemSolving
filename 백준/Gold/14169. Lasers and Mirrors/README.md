# [Gold I] Lasers and Mirrors - 14169 

[문제 링크](https://www.acmicpc.net/problem/14169) 

### 성능 요약

메모리: 10280 KB, 시간: 1236 ms

### 분류

너비 우선 탐색(bfs), 값 / 좌표 압축(coordinate_compression), 다익스트라(dijkstra), 그래프 이론(graphs), 그래프 탐색(graph_traversal)

### 문제 설명

<p>For some reason, Farmer John's cows always seem to be running laser light shows.</p>

<p>For their latest show, the cows have procured a large powerful laser -- so large, in fact, that they cannot seem to move it easily from the location where it was delivered. They would like to somehow send the light from the laser to the barn on the other side of FJ's property. Both the laser and the barn can be considered to be located at points in the 2D plane on a map of FJ's farm. The cows plan to point the laser so that it sends a beam of light out either horizontally or vertically (i.e., aligned with the x or y axes). They will then bounce this beam off a number of mirrors to direct it to the barn.</p>

<p>On the farm there are N fence posts (1≤N≤100,000) located at distinct 2D points (also distinct from the laser and the barn) at which the cows can mount mirrors. The cows can choose not to mount a mirror on a fence post, in which case the laser would simply pass straight over the top of the post without changing direction. If the cows do mount a mirror on a fence post, they align it diagonally like / or \ so that it will re-direct a horizontal beam of light in a vertical direction or vice versa.</p>

<p>Please compute the minimum possible number of mirrors the cows need to use in order to re-direct the laser to the barn.</p>

### 입력 

 <p>The first line of input contains 5 space-separated integers: N,x<sub>L</sub>,y<sub>L</sub>,x<sub>B</sub>,y<sub>B</sub>, where (x<sub>L</sub>,y<sub>L</sub>) is the location of the laser and (x<sub>B</sub>,y<sub>B</sub>) is the location of the barn. All coordinates are between 0 and 1,000,000,000.</p>

<p>The next N lines each contain the x and y locations of a fence post, both integers in the range 0…1,000,000,000.</p>

### 출력 

 <p>Please output the minimum number of mirrors needed to direct the laser to the barn, or -1 if this is impossible to do.</p>

