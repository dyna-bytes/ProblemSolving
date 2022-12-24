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

matrix operator * (const matrix& A, const matrix& B) {
    assert(A[0].size() == B.size());
    int R = A.size(), K = B.size(), C = B[0].size();
    matrix M(R, vll(C));
    for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++)
            for (int k = 0; k < K; k++)
                (M[r][c] += A[r][k] * B[k][c] % MOD) %= MOD;
    return M;
}

matrix matpow(matrix A, ll N) {
    assert(A.size() == A[0].size());
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
    
    ll N; cin >> N;
    matrix recurr = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 1}
    };
    matrix base = {
        {1},
        {1},
        {1}
    };

    auto res = matpow(recurr, N - 1) * base;
    cout << (res[0][0] + res[1][0] + res[2][0]) % MOD << endl;
    return 0;
}