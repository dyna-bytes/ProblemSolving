# [Gold V] 십자 찾기 - 32715 

[문제 링크](https://www.acmicpc.net/problem/32715) 

### 성능 요약

메모리: 75688 KB, 시간: 500 ms

### 분류

누적 합

### 제출 일자

2026년 2월 15일 18:03:44

### 문제 설명

<p>쿠는 $N\times M$ 크기의 모눈종이를 임의로 색칠하고 있다. 쿠는 색칠하던 도중 모눈종이에서 특정 크기의 십자 모양을 몇 개나 찾을 수 있을지 궁금해졌다. </p>

<p>$(r, c)$위치의 모눈을 기준으로 $(r-K, c)$부터 $(r+K, c)$까지, $(r, c-K)$부터 $(r, c+K)$까지 연속해 색칠되어 있다면 $(r, c)$에 크기가 $K$인 십자가 있다고 정의한다. </p>

<p>크기가 각각 $0, 1, 2$인 십자는 아래의 그림과 같을 때, 크기가 $K$인 십자의 개수를 구해보자.</p>

<p style="text-align: center;"><img alt="" src="https://upload.acmicpc.net/bd19208d-a5d8-4ef6-a3a2-eb68ddd6787e/-/preview/"></p>

### 입력 

 <p>첫째 줄에 모눈종이의 크기 $N$과 $M$이 공백으로 구분되어 주어진다. $\left(1\leq N, M\leq 2,500\right)$</p>

<p>둘째 줄에 십자의 크기 $K$가 주어진다. $\left(0\leq K\leq \left\lfloor\frac{min(N-1,\, M-1)}{2}\right\rfloor\right)$</p>

<p>셋째 줄부터 $N$줄에 걸쳐 모눈의 색칠 여부가 공백으로 구분되어 주어진다. 해당 위치가 색칠되어 있다면 <span style="color:#e74c3c;"><code>1</code></span>, 아니라면 <span style="color:#e74c3c;"><code>0</code></span>이다.</p>

### 출력 

 <p>크기가 $K$인 십자의 개수를 출력한다.</p>

