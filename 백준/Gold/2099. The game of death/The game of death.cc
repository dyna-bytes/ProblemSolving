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
typedef vector<int> vint;
typedef vector<pii> vpii;

vector<vint> matmul(const vector<vint>& A, const vector<vint>& B) {
    int R = A.size(), K = B.size(), C = B[0].size();
    vector<vint> M(R, vint(C));
    for (int r = 0; r < R; r++) 
        for (int c = 0; c < C; c++) 
            for (int k = 0; k < K; k++)
                M[r][c] |= A[r][k] * B[k][c]; // treat as boolean
    return M;
}

vector<vint> matsqr(const vector<vint>& A) {
    return matmul(A, A);
}

vector<vint> matpow(const vector<vint>& A, int K) {
    if (K == 2) return matsqr(A);
    if (K == 1) return A;

    if (K % 2 == 0) return matsqr(matpow(A, K/2));
    else return matmul(matsqr(matpow(A, K/2)), A);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int N, K, M;
    cin >> N >> K >> M;
    vector<vint> adj(N, vint(N));
    for (int from = 0; from < N; from++) {
        int to1, to2; cin >> to1 >> to2;
        to1--, to2--;
        adj[from][to1] = adj[from][to2] = 1;
    }

    auto ret = matpow(adj, K);
    for (int i = 0; i < M; i++) {
        int from, to; cin >> from >> to;
        from--, to--;
        cout << (ret[from][to] ? "death" : "life") << endl;
    }
    
    return 0;
}