/*
* https://m.blog.naver.com/kks227/221633584963
*/

#include <iostream>
#include <vector>
#include <complex>
#include <math.h>
#include <algorithm>

using namespace std;
const double PI = acos(-1);
typedef complex <double> cpx; // long double을 쓰면 2배 가량 느림
// double : 196 ms, long double : 412 ms

long N, M;
vector<cpx> X, Y;

void FFT(vector<cpx> &f, cpx w){
    int n = f.size();
    if (n == 1) return; // base case

    // 다항식 분리
    vector <cpx> even(n/2), odd(n/2);
    for(int i = 0; i < n; ++i)
        (i%2 ? odd : even)[i/2] = f[i];

    // divide: 각각의 다항식을 재귀적으로 DFT함
    FFT(even, w*w);
    FFT(odd, w*w);

    // conquer: 재귀적으로 알아온 DFT 값들로 이번 함수의 결과를 계산
    cpx w_k(1, 0);
    for (int wk = 0; wk < n/2; ++wk){
        // f(x) = f_even(x^2) + x * f_odd(x^2)
        f[wk] = even[wk] + w_k*odd[wk];
        // f(-x) = f_even(x^2) - x * f_odd(x^2)
        f[wk + n/2] = even[wk] - w_k*odd[wk];
        // w_k = w^k. w_k = w_1^k for the first time
        w_k *= w;
    }
}

void invFFT(vector<cpx> &f, cpx inv_w){
    int n = f.size();
    FFT(f, inv_w);
    for(int i = 0; i < n; ++i){
        f[i] /= cpx(n, 0);
        // 원래 다항식의 계수가 전부 정수일 때만 사용
        f[i] = cpx( round(f[i].real()), round(f[i].imag()) );
    }
}

vector<cpx> convolution(vector<cpx> &X, vector<cpx> &Y){
    vector<cpx> Z;
    int n = 1;
    while(n <= X.size() || n <= Y.size())  n *= 2;
    n *= 2;
    X.resize(n);
    Y.resize(n);
    Z.resize(n);

    cpx w(cos(2 * PI / n), sin(2 * PI / n));
    cpx inv_w = cpx(1, 0)/w;

    FFT(X, w);
    FFT(Y, w);

    for(int i = 0; i < n; ++i)
        Z[i] = X[i]*Y[i];
    
    invFFT(Z, inv_w);

    return Z;
}

void Input(vector<char> &A, vector<char> &B){
    cin >> N >> M;

    A.resize(N);
    B.resize(M);

    for(int i = 0; i < N; i++)
        cin >> A[i];
    for(int i = 0; i < M; i++)
        cin >> B[i];

    reverse(B.begin(), B.end());
}

int main(){
    vector<char> A, B;
    vector<cpx> X, Y, Z;
    Input(A, B);

    // A: S = 1, B: R = 1
    X.resize(N);
    Y.resize(M);

    for(long i = 0; i < N; i++){
        if(A[i] == 'S') X[i] = 1;
        else            X[i] = 0;
    }

    for(long i = 0; i < M; i++){
        if(B[i] == 'R') Y[i] = 1;
        else            Y[i] = 0;
    }

    Z = convolution(X, Y);

    vector<long> wins(N);

    for(long i = M - 1; i < N + M - 1; i++){
        long j = i - (M - 1);
        wins[j] = (long)Z[i].real();
    }
    
    // A: P = 1, B: S = 1
    X.clear();
    Y.clear();
    Z.clear();
    X.resize(N);
    Y.resize(M);

    for(long i = 0; i < N; i++){
        if(A[i] == 'P') X[i] = 1;
        else            X[i] = 0;
    }

    for(long i = 0; i < M; i++){
        if(B[i] == 'S') Y[i] = 1;
        else            Y[i] = 0;
    }

    Z = convolution(X, Y);

    for(long i = M - 1; i < N + M - 1; i++){
        long j = i - (M - 1);
        wins[j] += (long)Z[i].real();
    }

    // A: R = 1, B: P = 1
    X.clear();
    Y.clear();
    Z.clear();
    X.resize(N);
    Y.resize(M);

    for(long i = 0; i < N; i++){
        if(A[i] == 'R') X[i] = 1;
        else            X[i] = 0;
    }

    for(long i = 0; i < M; i++){
        if(B[i] == 'P') Y[i] = 1;
        else            Y[i] = 0;
    }

    Z = convolution(X, Y);

    for(long i = M - 1; i < N + M - 1; i++){
        long j = i - (M - 1);
        wins[j] += (long)Z[i].real();
    }
    
    long MAX = 0;
    for(long j = 0; j < N; j++){
        if(wins[j] > MAX){
            MAX = wins[j];
        }
    }
    cout << MAX;
    // for(auto i : wins)
    //     cout << i << " ";

    return 0;
}