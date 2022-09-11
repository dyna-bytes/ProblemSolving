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

int N, K;
vint coins;
vint dp;

/*
int f(int i, int k) {
    if (i == N) return (k == 0);

    int ret = f(i+1, k);
    if (k >= coins[i]) ret += f(i, k - coins[i]);
    return ret;
}
*/

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> N >> K;
    coins.resize(N);
    for(int i = 0; i < N; i++) 
        cin >> coins[i];

    dp.resize(K+1); // dp[k]: k원을 만드는 경우의 수
    
    // dp[k] = sum(coins[i]){ dp[k - coins[i]] }
    // k원을 만드는 경우의 수 = 가능한 모든 coins에 대해 k - coins원을 만드는 경우의 수의 합
    dp[0] = 1;
    for (int coin: coins) 
        for (int k = coin; k <= K; k++)
            dp[k] += dp[k - coin];
    cout << dp[K];

    return 0;
}