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
const ll MOD = 1e8 + 7;

matrix matmul(const matrix& A, const matrix& B) {
    assert (A[0].size() == B.size());
    int R = A.size(), C = B[0].size(), K = B.size();
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
    return matmul(A, A);
}

matrix matpow(const matrix& A, ll K) {
    if (K == 2) return matsqr(A);
    if (K == 1) return A;

    if (K % 2 == 0) return matsqr(matpow(A, K/2));
    else return matmul(matsqr(matpow(A, K/2)), A);
}

ll pow(int n) {
    ll ret = 1;
    ll x = 2;
    while (n > 0) {
        if (n % 2 == 1) (ret *= x) %= MOD;
        (x *= x) %= MOD;
        n /= 2;
    }
    return ret;
}

ll solve(ll K, ll N) {
    if (N <= K) return 1;
    if (K == 0) return pow(N);

    matrix base_case(K+1, {1});
    matrix A(K+1, vll(K+1));
    A[0][0] = A[0][K] = 1;
    for (int r = 1; r < K+1; r++)
        A[r][r-1] = 1;
    
    auto ret = matmul(matpow(A, N-K), base_case);
    // debugV2D(ret);
    return ret[0][0];
} 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int T; cin >> T;
    while(T--) {
        ll K, N; cin >> K >> N;
        cout << solve(K, N) << endl;
    }
}