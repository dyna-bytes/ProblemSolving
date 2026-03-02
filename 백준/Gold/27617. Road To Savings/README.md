# [Gold III] Road To Savings - 27617 

[문제 링크](https://www.acmicpc.net/problem/27617) 

### 성능 요약

메모리: 2156 KB, 시간: 0 ms

### 분류

그래프 이론, 최단 경로, 데이크스트라

### 제출 일자

2026년 3월 2일 20:20:56

### 문제 설명

<p>Pat Wholes is in charge of road maintenance in Capitol City, and boy do those roads need maintenance.  The road conditions are so poor that accidents have become almost a daily event, and the surviving public is in an uproar.  Now while Pat would love to pave every road in the city, he also wants to keep his job.  The cost of all that paving would certainly upset the mayor, who would just as certainly replace Pat if he spends too much.  So now the decision is: which roads get paved and which don't? After thinking about this problem -- and his job security -- Pat came up with a bright idea: since the ultimate goal is to keep the mayor happy, he'll pave only those roads that are on a shortest path from the mayor's house to the mayor's office.  There actually might be several ways for the mayor to drive to work that are equally short, but that should still leave plenty of roads that aren't on any of these paths and hence plenty of roads that don't need to be paved (hopefully).  Pat's come down to your cubicle in the basement to ask you to determine the length of roads that don't need to be paved.</p>

### 입력 

 <p>Input starts with four positive integers $n$ $m$ $a$ $b$ ($n, a, b \leq 100, a \neq b$) where $n$ indicates the number of intersections in the town (numbered $1$ to $n$), $m$ is the number of roads connecting intersections, and $a$ and $b$ are the intersections where the mayor's house and office are located, respectively.  Following this are $m$ lines, each containing a triplet of numbers $i_1$ $i_2$ $\ell$ ($1 \leq i_1, i_2 \leq n, i_1 \neq i_2,  1 \leq \ell \leq 100$) indicating a two-way road exists between intersection $i_1$ and $i_2$ with length $\ell$.  At most one road exists between any two intersections and at least one path exists between $a$ and $b$.</p>

### 출력 

 <p>Output the total length of all roads that don't need to be paved.</p>

