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
const ll INF = 1e9 + 1;

int N, K;
ll total_E;
vll E;
vll dp; 
// dp[i] : i번째 칸을 밟았을 때의 최소 dp 합
// dp[i] = E[i] + min{ dp[i-K] ~ dp[i-1] }
// 반드시 첫 칸과 마지막 칸을 밟아야 함

void solve() {
    deque<pll> deq;

    for (int i = 0; i < N+2; i++) {
        while (!deq.empty() && deq.front().first < i - K - 1)
            deq.pop_front();
        
        dp[i] = E[i] + (deq.empty() ? 0 : deq.front().second);

        while (!deq.empty() && deq.back().second >= dp[i])
            deq.pop_back();

        deq.push_back({i, dp[i]});
    }
    
    cout << total_E - dp[N+1];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> N >> K;
    E.resize(N+2);
    dp.resize(N+2);
    for (int i = 1; i <= N; i++) {
        cin >> E[i];
        total_E += E[i];
    }

    solve();
    
    return 0;
}