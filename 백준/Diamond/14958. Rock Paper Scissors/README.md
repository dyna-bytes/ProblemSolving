# [Diamond V] Rock Paper Scissors - 14958 

[문제 링크](https://www.acmicpc.net/problem/14958) 

### 성능 요약

메모리: 27548 KB, 시간: 456 ms

### 분류

고속 푸리에 변환(fft), 수학(math)

### 문제 설명

<p>There is a Rock Paper Scissors (RPS) machine which generates Rock, Paper, or Scissors randomly. You also have a similar small Rock Paper Scissors machine. Before the game, the RPS machine will generate a list of its choice of Rock, Paper, or Scissors of the length <em>n</em> and your machine also will generates a list of its choice of the length <em>m</em>. That is, you know the whole list of the RPS’s choices and you have the list of your machine’s choices. Of course, each choice of the machines is one of the three options (Rock, Paper, or Scissors).</p>

<p>Now, you start playing Rock Paper Scissors game. In every match, you compare the list of RPS’s choice and the list of your machine’s in sequence and decide whose machine would win. However, only you may skip some RPS’s choices to find the position to get the most winning points of your machine. After you decide to start match you cannot skip the match till the end of the match. ‘<code>R</code>’ stands for Rock, ‘<code>P</code>’ stands for Paper, and ‘<code>S</code>’ stands for Scissors.</p>

<p>For example, suppose that the RPS’s list is “<code>RSPPSSSRRPPR</code>” and your machine’s list is “<code>RRRR</code>”. To get the most winning points, you should start the match after skipping three RPS’s choices or four RPS’s choices. (See Figure H.1.) Then, you can win in three matches. The draw case is not considered.</p>

<p style="text-align:center"><img alt="" src="https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/14958/1.png" style="height:128px; width:652px"></p>

<p style="text-align:center">Figure H.1. The most winning position against RPS machine when <em>n</em> = 12 and <em>m</em> = 4.</p>

<p>Given the list of RPS’s choices and the list of your choices, find the position to get the maximum number of wining matches.</p>

### 입력 

 <p>Your program is to read from standard input. The first line contains two positive integers <em>n</em> and <em>m</em> (1 ≤ <em>m</em> < <em>n</em> ≤ 100,000), where <em>n</em> is the length of the string for RPS machine and <em>m</em> is the length of the string for your machine. Following the first line contains the list of choices of RPS machine and the second line contains the list of choices of your machine.</p>

### 출력 

 <p>Your program is to write to standard output. The first line should contain an integer indicating the maximum number of wining matches</p>

