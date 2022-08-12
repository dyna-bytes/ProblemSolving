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
const ll MOD = 1e9 + 9;

/**
 * @brief dp + prefix sum
 * 두 수열 A, B에서 각각 길이가 K인 부분 수열을 골라서 정렬함.
 * A의 부분 수열의 모든 항 > B의 부분 수열의 모든 항인 경우의 수는?
 * 
 * 점화식:
 * team(i, j, k): 구간 [i, N), [j, M)에서 A[] > B[]를 만족하는 
 * 길이 k인 부분 수열을 각각 고를 수 있는 경우의 수
 * 
 * team(i, j, k) = sum(i <= a < N, j <= b < M, A[a] > B[b]){ team(a+1, b+1, k-1) }
 */

int N, M, K;
int A[1001], B[1001];
ll dp[10][1001][1001];
ll dpSum[10][1001][1001]; // dpSum[k][i][j]: sum(0 <= a < i, 0 <= b < j) dp[k][a][b]

/*
int f(int i, int j, int k) {
    if (k == 0) return 1;
    if (i == N || j == M) return 0;

    int& ret = dp[k][i][j];
    // O(NM)이 걸려버림
    for (int a = i; a < N; a++)
        for (int b = j; b < M; b++)
            if (A[a] > B[b]) ret += f(a+1, b+1, k-1);
    return ret;
}
*/

int f() {
    // 문제의 방향을 바꿔 k = 0부터 푼다.
    for (int k = 0; k < K; k++) {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                if (A[i] > B[j]) dp[k][i][j] = k > 0 ? dpSum[k-1][i][j] : 1; // dpSum[i][j]: dp[0][0] ~ dp[i-1][j-1]까지 dp의 모든 합
                
        // 한 k층에 대한 dp[i][j]의 합을 미리 모두 구해둔다.
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                dpSum[k][i+1][j+1] = (dpSum[k][i+1][j] + dpSum[k][i][j+1] - dpSum[k][i][j] + dp[k][i][j]
                + MOD) % MOD;
    }
    return dpSum[K-1][N][M];
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> N >> M >> K;
    for (int i = 0; i < N; i++) cin >> A[i];
    for (int i = 0; i < M; i++) cin >> B[i];
    sort(A, A+N);
    sort(B, B+M);
    cout << f();
    return 0;
}