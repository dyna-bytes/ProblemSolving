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

ll gcd(ll x, ll y) {
    if (y == 0) return x;
    if (x < y) swap(x, y);
    return gcd(y, x % y);
}
/**
 * @brief 모든 수를 k로 나눈 나머지만 보관
 * 
 * 어떤 두 수 a, b의 길이가 각각 la, lb 일 때,
 * a, b를 이어붙인 수 x는 x = a * 10^lb + b 이다.
 * 
 * 이때, 
 *   a * 10^lb mod k = (a mod k)(10^lb mod k) mod k
 *   Thus, x mod k = (a mod k)(10^lb mod k) mod k + (b mod k)
 * a mod k, b mod k는 입력을 받으며 전처리, 10^lb mod k는 50자리까지 한자리씩 늘려가며 전처리 해둠.
 * 
 * DP[s][n]: 현재까지 집합 s에 포함된 숫자들로 수 n를 만들었을 때,
 * 남을 수들을 이용해 만들 수 있는 k로 나누어 떨어지는 수의 개수
 * 
 * DP[s][a] = sum(~s){ DP[~s][a * 10^b_size + b] } // b: 집합 ~s의 원소
 * if (s == 전체집합) and (~s == 공집합)
 *   DP[~s][n] = 1 if (n % k == 0), else 0
 */
int N, K;
vint ten_powered(51);
vector<string> A(16);
vpii pre(16);
ll dp[1 << 15][101];

ll dfs(int s, int a) {
    if (s == (1 << N) - 1) return (a % K == 0);

    ll& ret = dp[s][a];
    if (ret != -1) return ret;

    ret = 0;
    for (int next = 0; next < N; next++) {
        if (s & (1 << next)) continue;
        auto [b, b_size] = pre[next];
        ll next_a = a * ten_powered[b_size] + b;
        next_a %= K;
        ret += dfs(s | (1 << next), next_a);
    }
    return ret;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> N;
    ll all = 1;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        all *= (i + 1);
    }
    cin >> K;

    // 10^lb mod k 전처리
    ten_powered[0] = 1 % K;
    for (int i = 1; i < 51; i++)
        ten_powered[i] = (ten_powered[i-1] * 10) % K;

    // b mod k와 lb(b_size)를 미리 구해둠
    for (int i = 0; i < N; i++) {
        reverse(A[i].begin(), A[i].end());
        for (int j = 0; j < A[i].size(); j++)
            pre[i].first += (A[i][j] - '0') * ten_powered[j] % K;
        // pre[i].first %= K;   
        // b mod k = (c * 10^ld) mod k = (c mod k)(10^ld mod k) mod k 

        pre[i].second = A[i].size();
    }

    memset(dp, -1, sizeof(dp));
    ll cnt = dfs(0, 0);
    ll g = gcd(all, cnt);
    cout << cnt / g << "/" << all / g;
    return 0;
}