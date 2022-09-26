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
const ll MOD = 1e6 + 3;

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


matrix matpow(const matrix& A, ll K) {
    if (K == 1) return A;

    matrix sqrt = matpow(A, K/2);
    if (K % 2 == 0) return sqrt * sqrt;
    else return sqrt * sqrt * A;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll N, S, E, T;
    cin >> N >> S >> E >> T;
    matrix adj(N*5, vll(N*5));

    for (int from = 0; from < N; from++) {
        string path; cin >> path;
        for (int to = 0; to < N; to++) {
            int additional_path = path[to] - '0' - 1;
            if (additional_path >= 0) adj[from * 5][to * 5 + additional_path] = 1;

        }
        for (int inside_path = 0; inside_path < 4; inside_path++)
            adj[from * 5 + inside_path + 1][from * 5 + inside_path] = 1;
    }

    S--, E--;
    // debugV2D(adj);
    cout << matpow(adj, T)[S * 5][E * 5] % MOD;
    
    return 0;
}