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
        for (int c = 0; c < C; c++) 
            for (int k = 0; k < K; k++)
                (M[r][c] += A[r][k] * B[k][c] % MOD) %= MOD;
        
    return M;
}

matrix matsqr(const matrix& A) {
    return A * A;
}

/**
 * @brief Divide and Conquer
 * if K is even: A^K = A^(K/2)^2
 * else: A^K = A^(K/2)^2 * A
 */
matrix matpow(const matrix& A, ll K) {
    assert (A.size() == A[0].size());
    if (K == 1) return A;

    if (K % 2 == 0) return matsqr(matpow(A, K/2));
    else return matsqr(matpow(A, K/2)) * A;
}


/**
 * @brief bit-shifting
 * Let K = B0(2) + B1(2) + B2(2)  
 * where B(2) is a binary number, and all of B(2)'s bits are 0
 * except only MSB(which is 1)
 * ex) 11 = 1000(2) + 10(2) + 1(2)
 * 
 * Then, A^K becomes
 * A^K = A^B0(2) * A^B1(2) * A^B2(2)
 *     = A^2^len(B0) * A^2^len(B1) * A^2^len(B2)
 * ex) 4^11 = 4^8 * 4^2 * 4^1
 */
matrix matpow(matrix& A, ll N) {
    assert (A.size() == A[0].size());
    matrix ret(A.size(), vll(A.size()));
    for (int i = 0; i < A.size(); i++) ret[i][i] = 1; // ret = I

    while (N) {
        if (N & 1) ret = ret * A;
        A = A * A;
        N /= 2;
    }
    return ret;
}


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