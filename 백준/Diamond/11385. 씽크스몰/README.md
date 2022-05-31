# [Diamond IV] 씽크스몰 - 11385 

[문제 링크](https://www.acmicpc.net/problem/11385) 

### 성능 요약

메모리: 248000 KB, 시간: 3180 ms

### 분류

중국인의 나머지 정리(crt), 고속 푸리에 변환(fft), 수학(math), 정수론(number_theory)

### 문제 설명

<p>많이 자란 정민이는 부모님이 시키는 유명한 학습지 씽크스몰을 해야 한다. 정민이가 이번에 배워야 하는 부분은 다항식의 곱셈이다. 하지만 정민이는 게임을 해야만 하기에, 여러분에게 점수를 줄 테니 다항식 f(x)와 다항식 g(x)를 곱해주는 프로그램을 작성해 달라고 한다.</p>

### 입력 

 <p>첫 번째 줄에 다항식 f(x)의 차수 N (1 ≤ N ≤ 1,000,000)과 다항식 g(x)의 차수 M (1 ≤ M ≤ 1,000,000)이 공백을 사이로 두고 주어진다.</p>

<p>두 번째 줄에는 다항식 f(x)의 계수를 나타내는 N + 1개의 자연수 a<sub>0</sub>, a<sub>1</sub>, ..., a<sub>N-1</sub>, a<sub>N</sub>이 주어진다. f(x) = a<sub>0</sub> + a<sub>1</sub>·x + a<sub>2</sub>·x<sup>2</sup> + ... + a<sub>N-1</sub>·x<sup>N-1</sup> + a<sub>N</sub>·x<sup>N</sup>이다. (1 ≤ a<sub>i</sub> ≤ 1,000,000)</p>

<p>세 번째 줄에는 다항식 g(x)의 계수를 나타내는 M + 1개의 자연수 b<sub>0</sub>, b<sub>1</sub>, ..., b<sub>M-1</sub>, b<sub>M</sub>이 주어진다. g(x) = b<sub>0</sub> + b<sub>1</sub>·x + b<sub>2</sub>·x<sup>2</sup> + ... + b<sub>M-1</sub>·x<sup>M-1</sup> + b<sub>M</sub>·x<sup>M</sup>이다. (1 ≤ b<sub>i</sub> ≤ 1,000,000)</p>

### 출력 

 <p>f(x) × g(x) = c<sub>0</sub> + c<sub>1</sub>·x + c<sub>2</sub>·x<sup>2</sup> + ... + c<sub>L</sub>·x<sup>L</sup>라고 하자.</p>

<p>첫 번째 줄에 c<sub>0</sub>, c<sub>1</sub>, ..., c<sub>L</sub>의 값을 모두 xor한 값, 즉 c<sub>0</sub> ⊕ c<sub>1</sub> ⊕ ... ⊕ c<sub>L</sub>을 출력한다. C/C++에서는 c[0] ^ c[1] ^ ... ^ c[L-1] ^ c[L]의 값을 구하면 된다.</p>

<p>xor 연산을 시행하는 이유는, c<sub>i</sub>를 출력하기에는 그 양이 너무 많기 때문이며, 문제의 풀이에는 영향을 주지 않는다.</p>

<p> </p>

