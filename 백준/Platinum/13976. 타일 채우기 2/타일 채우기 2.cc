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
const ll MOD = 1e9 + 7;

// matmul A[r*k] B[k*c] = M[r*c]
matrix operator * (const matrix& A, const matrix& B) {
    assert (A[0].size() == B.size());
    int R = A.size(), K = B.size(), C = B[0].size();
    matrix M(R, vll(C));
    for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++) 
            for (int k = 0; k < K; k++)
                (M[r][c] += ((A[r][k] * B[k][c] + MOD) % MOD)) %= MOD;
        
    return M;
}

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

/**
 * @brief 점화식
 * let dp[0] = 1
 * dp[2] = 3dp[0]
 * dp[4] = 3dp[2] + 2dp[0]
 * dp[6] = 3dp[4] + 2dp[2] + 2dp[0]
 * 
 * dp[2N] = 3dp[2(N-1)] + 2 * SUM(0 <= i < N-1)dp[2i]
 * 
 * for even N 
 * dp[N]   = 3dp[N-2] + 2dp[N-4] + 2dp[N-6] + ... + 2dp[0]
 * dp[N-2] = 3dp[N-4] + 2dp[N-6] + 2dp[N-8] + ... + 2dp[0]
 * 
 * dp[N] - dp[N-2] = 3dp[N-2] - dp[N-4]
 * Thus, dp[N] = 4dp[N-2] - dp[N-4]
 * 
 * [dp[N]    = [4 -1]^(N/2-1) [3
 *  dp[N-2]]   [1  0]          1]
 */

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    ll N;
    cin >> N;
    if (N % 2) {
        cout << 0;
        return 0;
    }

    matrix base_case = {
        {3},
        {1}
    };

    matrix A = {
        {4, -1},
        {1, 0}
    };

    auto ret = matpow(A, N/2-1) * base_case;
    cout << ret[0][0] % MOD;
    // debugV2D(ret);
    
    return 0;
}