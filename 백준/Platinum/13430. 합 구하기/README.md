# [Platinum V] 합 구하기 - 13430 

[문제 링크](https://www.acmicpc.net/problem/13430) 

### 성능 요약

메모리: 2156 KB, 시간: 16 ms

### 분류

조합론(combinatorics), 분할 정복을 이용한 거듭제곱(exponentiation_by_squaring), 수학(math), 모듈로 곱셈 역원(modular_multiplicative_inverse), 정수론(number_theory)

### 문제 설명

<p>S는 다음과 같이 정의된다.</p>

<ul>
	<li>S(0, n) = n (모든 양의 정수 n)</li>
	<li>S(k, n) = S(k-1, 1) + S(k-1, 2) + ... + S(k-1, n) (모든 양의 정수 k, n)</li>
</ul>

<p>k와 n이 주어졌을 때, S(k, n)을 1,000,000,007로 나눈 나머지를 구하는 프로그램을 작성하시오.</p>

### 입력 

 <p>첫째 줄에 k와 n이 주어진다. (1 ≤ k ≤ 50, 1 ≤ n ≤ 1,000,000,000)</p>

### 출력 

 <p>첫째 줄에 S(k, n)을 1,000,000,007로 나눈 나머지를 출력한다.</p>

