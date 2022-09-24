#include <bits/stdc++.h>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define debugVec(v) do { \
    std::cout << "[Debug] ["; \
    for(int i = 0; i < ((v.size())-1); i++) std::cout << v[i] << "|"; \
    std::cout << v[((v.size())-1)] << "]\n"; \
} while(0)
#define debugV2D(v) do { \
    std::cout << "[Debug] [\n"; \
    for(int y = 0; y < (v.size()); y++) { \
        if(v[y].empty()){ std::cout << "  []\n"; continue; } \
        std::cout << "  ["; \
        for(int x = 0; x < ((v[y].size())-1); x++) \
            std::cout << v[y][x] << "|"; \
        std::cout << v[y][(v[y].size())-1] << "]\n"; \
    } \
    std::cout << "]\n"; \
} while(0)
#define endl '\n'
typedef long long ll;
typedef vector<ll> vll;
typedef vector<vll> matrix;
const ll MOD = 1000;

// matmul A[R * K] B[K * C] = M[R * C]
matrix operator * (const matrix& A, const matrix& B) {
    assert (A[0].size() == B.size());
    int R = A.size(), K = B.size(), C = B[0].size();
    matrix M(R, vll(C));
    for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++) {
            for (int k = 0; k < K; k++)
                M[r][c] += A[r][k] * B[k][c] % MOD;
            M[r][c] %= MOD;
        }
    return M;
}

matrix matsqr(const matrix& A) {
    return A * A;
}

matrix matpow(const matrix& A, ll K) {
    if (K == 2) return matsqr(A);
    if (K == 1) return A;

    if (K % 2 == 0) return matsqr(matpow(A, K/2));
    else return matsqr(matpow(A, K/2)) * A;
}

/**
 * @brief 분할정복
 * if K is even: A^K = A^(K/2)^2
 * else: A^K = A^(K/2)^2 * A
 */

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    // Usage example
    // problem BOJ 10830: https://www.acmicpc.net/problem/10830
    
    int N; ll K;
    cin >> N >> K;
    vector<vll> A(N, vll(N));

    for (int r = 0; r < N; r++)
        for (int c = 0; c < N; c++)
            cin >> A[r][c];

    auto ret = matpow(A, K);    
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++)
            cout << ret[r][c] % MOD << ' ';
        cout << endl;
    }
    return 0;
}