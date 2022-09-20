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
typedef vector<int> vint;
typedef vector<vint> vvint;
const int MOD = 100;

vvint matmul(const vvint& A, const vvint& B) {
    int R = A.size(), K = B.size(), C = B[0].size();
    vvint M(R, vint(C));
    for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++) {
            for (int k = 0; k < K; k++) 
                M[r][c] += A[r][k] * B[k][c];
            M[r][c] %= MOD;
        }
    return M;
}

vvint matsqr(const vvint& A) {
    return matmul(A, A);
}

vvint matpow(const vvint& A, int K) {
    if (K == 2) return matsqr(A);
    if (K == 1) return A;

    if (K % 2 == 0) return matsqr(matpow(A, K/2));
    else return matmul(matsqr(matpow(A, K/2)), A);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int x, y, a0, a1, N;
    cin >> x >> y >> a0 >> a1 >> N;
    cout.width(2);
    cout.fill('0');
    
    if (N == 0) { cout << a0; return 0; }
    if (N == 1) { cout << a1; return 0; }

    vvint ignition_mat = {
        {x, y}, 
        {1, 0}
    };
    vvint base_case = {
        {a1}, 
        {a0}
    };

    auto ret = matmul(matpow(ignition_mat, N-1), base_case);
    cout << ret[0][0];
    return 0;
}