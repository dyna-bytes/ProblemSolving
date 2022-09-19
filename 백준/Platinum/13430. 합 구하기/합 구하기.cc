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
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vint;
typedef vector<ll> vll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;
const ll MOD = 1e9 + 7;

// A[R * K] B[K * C] = M[R * C]
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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    ll K, N;
    cin >> K >> N;
    if (N == 1) {
        cout << 1;
        return 0;
    }

    ll len = K + 2;
    // 점화식 행렬
    vector<vll> lower_triangular_mat(len, vll(len));
    // base case
    vector<vll> ones(len, {1});
    
    for (int r = 0; r < len; r++)
        for (int c = 0; c <= r; c++)
            lower_triangular_mat[r][c] = 1;

    auto ret = matmul(matpow(lower_triangular_mat, N-1), ones);
    cout << ret[len - 1][0] % MOD;
    return 0;
}