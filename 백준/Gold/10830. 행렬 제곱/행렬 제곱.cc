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
const ll MOD = 1000;

vector<vll> matmul(const vector<vll>& A, const vector<vll>& B) {
    int N = A.size();
    vector<vll> C(N, vll(N));
    for (int r_A = 0; r_A < N; r_A++) 
        for (int c_B = 0; c_B < N; c_B++) {
            for (int k = 0; k < N; k++)
                C[r_A][c_B] += A[r_A][k] * B[k][c_B];
            C[r_A][c_B] %= MOD;
        }
    return C;
}

vector<vll> matsqr(const vector<vll>& A) {
    return matmul(A, A);
}

/**
 * @brief 분할정복
 * if B is even: A^B = A^(B/2)^2
 * else: A^B = A^(B/2)^2 * A
 */

vector<vll> matpow(vector<vll>& A, ll K) {
    if (K == 2) return matsqr(A);
    if (K == 1) return A;

    if (K % 2 == 0) return matsqr(matpow(A, K/2));
    else return matmul(matsqr(matpow(A, K/2)), A);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

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