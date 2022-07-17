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
        std::cout << "  ["; \
        for(int x = 0; x < ((v[y].size())-1); x++) \
            std::cout << v[y][x] << "|"; \
        std::cout << v[y][(v[y].size())-1] << "]\n"; \
    } \
    std::cout << "]\n"; \
} while(0)
#define endl '\n'
typedef long long ll;
typedef pair<int, int> P;

/**
 * @brief 누적학 + dp(경우의 수)
 * 
 * 누적합 = n*division인 곳을 다시 방문했다는 것은 
 * 이전에 누적합이 n*division 이었던 곳과 현재 누적합이 n*division 인 곳 사이에
 * 누적합이 0인 세트가 존재함을 의미한다.
 * 
 * 이 세트는 수열을 각 합이 division인 n개의 덩어리로 구분할 수 있는 경우의 수에 영향을 미치지 않으며,
 * 합이 n*division인 1개의 덩어리로 구분할 수 있는 경우의 수에도 영향을 미치지 않는다.
 * (한편 이때 합이 n*division인 1개의 덩어리에는 이전에 이 덩어리를 각 n개의 덩어리로 쪼갤 수 있는 경우의 수가 담겨있다.)
 */

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N; cin >> N;
    vector<ll> prefix_sum(N+1); // one base index

    for (int i = 0; i < N; i++) {
        ll inp; cin >> inp;
        prefix_sum[i+1] = prefix_sum[i] + inp;
    }

    if (prefix_sum[N] % 4) {
        cout << 0;
        return 0;
    }

    ll division = prefix_sum[N] / 4;
    vector<ll> dp = {1, 0, 0, 0};
    // dp[i]: 빗금을 i개 칠 수 있는 경우의 수
    // dp[i] = dp[i] + dp[i-1]: 빗금을 i개 칠 수 있는 경우의 수 + 빗금을 i-1개 칠 수 있는 경우의 수

    for (int i = 1; i < N; i++) {
        if (prefix_sum[i] == 3 * division)
            dp[3] += dp[2];
        if (prefix_sum[i] == 2 * division)
            dp[2] += dp[1];
        if (prefix_sum[i] == 1 * division)
            dp[1] += dp[0];
    }
    cout << dp[3];

    return 0;
}