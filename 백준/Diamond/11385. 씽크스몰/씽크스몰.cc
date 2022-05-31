/*
* https://casterian.net/archives/297#comment-173
* https://tistory.joonhyung.xyz/6
*/

#include <iostream>
#include <vector>
#include <complex>
#include <math.h>
#include <algorithm>

using namespace std;
const long double PI = acos(-1.L);
typedef complex <long double> cpx;

unsigned N, M;

inline unsigned bitreverse(const unsigned n, const unsigned k){
    unsigned r, i;
    for (r = 0, i = 0; i < k; ++i)
        r |= ((n >> i) & 1) << (k - i - 1);
    return r;
}

void fft(vector<cpx> &f, bool is_reverse=false){
    const unsigned n = f.size();
    const unsigned log_n = __builtin_ctz(n);
    // while ((1 << log_n) < n) log_n++; // 2^log_n' >= n --> n' >= n

    for (unsigned i = 0; i < n; ++i){
        unsigned j = bitreverse(i, log_n);
        if (i < j) 
            swap(f[i], f[j]);
    }

    for (unsigned N = 2; N <= n; N *= 2){ // N is step size
        // long double theta = 2*PI/N * (is_reverse? -1 : 1);
        // cpx w = {cos(theta), sin(theta)}; // w = epx(2PI/N). step unity root where period is N 
        vector<cpx> w(N/2);
        for (unsigned i = 0; i < N/2; ++i){
            long double t = 2*PI*i/N * (is_reverse? -1 : 1);
            w[i] = cpx(cos(t), sin(t));
        }

        for (unsigned i = 0; i < n; i += N){ // jump by step size N
            // cpx w_n(1, 0); // w_n = w^n = exp(2PI/N * n)
            
            for (unsigned j = 0; j < N/2; ++j){
                cpx odd = w[j] * f[i + j + N/2];   // w^n * fft{a_odd} (N/2 뒤의 항)
                f[i + j + N/2] = f[i + j] - odd;    // fft{a(n + N/2)} = fft{a_even(n)} - w^n * fft{a_odd(n)}
                f[i + j]       = f[i + j] + odd;    // fft{a(n)}       = fft{a_even(n)} + w^n * fft{a_odd(n)}
                // w_n *= w;
            }
        }
    }

    if(is_reverse)
        for(unsigned i = 0; i < n; i++){
            f[i] /= n;
            f[i] = cpx( round(f[i].real()), round(f[i].imag()) );
        }
}

vector<cpx> multiply(vector<cpx> &X, vector<cpx> &Y){
    int n = max(X.size(), Y.size());
    // while(n <= X.size() || n <= Y.size()) n *= 2;
    // n *= 2;
    // while(n < 2*max(N+1, M+1) - 1) n *= 2;

    // X.resize(n);
    // Y.resize(n);
    vector<cpx> Z(n);

    fft(X);
    fft(Y);

    for(int i = 0; i < n; ++i)
        Z[i] = X[i] * Y[i];

    fft(Z, true);
    
    return Z;
}

void Input(vector<cpx> &X, vector<cpx> &Y){
    
    cin >> N >> M;

    unsigned n = 1;
    while(n < 2*max(N+1, M+1) - 1) n *= 2;

    X.resize(n);
    Y.resize(n);

    for(unsigned i = 0; i < N + 1; ++i)
        cin >> X[i];
    for(unsigned i = 0; i < M + 1; ++i)
        cin >> Y[i];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<cpx> X, Y, Z;
    Input(X, Y);
    Z = multiply(X, Y);
    unsigned L = N + M;

    unsigned long long z = 0; //Z[0].real();
    for(unsigned i = 0; i < L + 1 ; ++i)
        z ^= (unsigned long long)Z[i].real();

    cout << z;

    return 0;
}
