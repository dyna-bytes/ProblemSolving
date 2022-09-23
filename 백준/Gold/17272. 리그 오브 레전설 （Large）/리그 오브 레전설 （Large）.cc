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
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<pll> vpll;
const ll MOD = 1e9 + 7;

vector<vll> matmul(const vector<vll>& A, const vector<vll>& B) {
    int R = A.size(), C = B[0].size(), K = B.size();
    vector<vll> M(R, vll(C));
    for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++) {
            for (int k = 0; k < K; k++)
                M[r][c] += A[r][k] * B[k][c] % MOD;
            M[r][c] %= MOD;
        }
    return M;
}

vector<vll> matsqr(const vector<vll>& A) {
    return matmul(A, A);
}

vector<vll> matpow(const vector<vll>& A, ll K) {
    if (K == 2) return matsqr(A);
    if (K == 1) return A;

    if (K % 2 == 0) return matsqr(matpow(A, K/2));
    else return matmul(matsqr(matpow(A, K/2)), A);
}

/**
 * @brief DP 행렬 최적화
 * 
 * k초에서의 스킬 조합 개수: a_k = a_(k-1) + a_(k-M)
 * base case: a_0 = a_1 = ... a_(M-1) = 1
 * 
 */

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll N, M;
    cin >> N >> M;
    if (N < M) {
        cout << 1 << endl;
        return 0;
    }

    // fill base case under k < M
    vector<vll> base_case(M, vll(M));
    for (int r = 0; r < M; r++)
        base_case[r][r] = 1;

    vector<vll> ignition_mat(M, vll(M));
    ignition_mat[0][0] = 1;
    ignition_mat[0][M-1] = 1;
    for (int r = 1; r < M; r++)
        ignition_mat[r][r-1] = 1;

    auto ret = matmul(matpow(ignition_mat, N), base_case);
    cout << ret[0][0] << endl;
    // debugV2D(ret);
    return 0;
}