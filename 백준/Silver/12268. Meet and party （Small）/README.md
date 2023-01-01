# [Silver IV] Meet and party (Small) - 12268 

[문제 링크](https://www.acmicpc.net/problem/12268) 

### 성능 요약

메모리: 2032 KB, 시간: 8 ms

### 분류

브루트포스 알고리즘(bruteforcing), 기하학(geometry)

### 문제 설명

<p>Little Sin lives in a Manhattan-grid city, a 2D plane where people can only go north, west, south or east along the grid. The distance from (x1, y1) to (x2, y2) is |x1 - x2| + |y1 - y2|.</p>

<p>Little Sin really likes to party and is hoping to host a house party in Manhattan this Sunday. Little Sin has collected a list of people who will attend, and now needs to decide at whose home she will host the party.</p>

<p>Little Sin invited all of the people in several rectangular areas, and all of those people have said yes. A rectangular area is denoted as (x1, y1, x2, y2), where x1 ≤ x2, y1 ≤ y2. People who live in a rectangular area fill all integral points inside it. So there are a total of (x2 - x1 + 1) * (y2 - y1 + 1) people in the rectangular area (x1, y1, x2, y2).</p>

<p>Little Sin knows the coordinates of those rectangular areas. She wants the party to be hosted at the home of one of the people who is attending, but she also doesn't want everyone else to have to travel very far: she wants to minimize the sum of all distances from all attendees' houses to the party. Can you help her?</p>

### 입력 

 <p>The first line of the input gives the number of test cases, <strong>T</strong>. <strong>T</strong> test cases follow. Each test case starts with a line containing a single integer: the number of rectangular areas, <strong>B</strong>. <strong>B</strong> lines follow. Each line contains 4 integers: x1, y1, x2, y2, denoting the coordinates of a rectangular area of people Little Sin has invited to her party.</p>

### 출력 

 <p>For each test case, output one line containing "Case #t: x y d", where t is the case number (starting from 1) and (x, y) is the coordinates of the person whose home the party should be hosted. If there are multiple positions with the same minimum total distance, choose the one with the smallest x. If there are still multiple positions, choose the one with the smallest y. The value d is the sum of the distances from all attendees' houses to the point (x, y).</p>

