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

int solve(int N, int K, vint& coins) {
    vector<vint> dp(2, vint(K+1));
    dp[0][0] = 1;

    for (int n = 0; n < N; n++) {
        for (int k = 0; k <= K; k++) {
            if (k + coins[n] <= K) dp[0][k + coins[n]] += dp[0][k];
            dp[1][k] = dp[0][k];
        }

        dp[0] = dp[1];
    }

    return dp[0][K];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N, K; cin >> N >> K;
    vint coins(N);
    for (int i = 0; i < N; i++) cin >> coins[i];

    cout << solve(N, K, coins);
    return 0;
}