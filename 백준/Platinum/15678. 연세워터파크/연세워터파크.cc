#include <bits/stdc++.h>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define debugVec(v) do { \
    std::cout << "[Debug] ["; \
    for(ll i = 0; i < ((v.size())-1); i++) std::cout << v[i] << "|"; \
    std::cout << v[((v.size())-1)] << "]\n"; \
} while(0)
#define debugV2D(v) do { \
    std::cout << "[Debug] [\n"; \
    for(ll y = 0; y < (v.size()); y++) { \
        if(v[y].empty()){ std::cout << "  []\n"; continue; } \
        std::cout << "  ["; \
        for(ll x = 0; x < ((v[y].size())-1); x++) \
            std::cout << v[y][x] << "|"; \
        std::cout << v[y][(v[y].size())-1] << "]\n"; \
    } \
    std::cout << "]\n"; \
} while(0)
#define endl '\n'
typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<pll> vpll;
const ll INF = 1e18 + 1;

#define idx first
#define dp_val second

ll N, D;
vll K;
vll dp;

/* O(n^2) 풀이. bottom-up 방식
ll f(){
    // dp[end]: 도착점 end에서 탈출할 시 얻을 수 있는 최대 점수
    // dp[end] = K[end] + max(end-D <= mid <= end){ dp[mid] }

    ll res = -INF;
    for (ll end = 0; end < N; end++) {
        ll max_dp_mid = -INF;

        // 구간 내의 최대 dp값을 찾아서 현재의 K값을 더해야함
        for (ll mid = max(end-D, 0); mid <= end; mid++) 
            max_dp_mid = max(max_dp_mid, dp[mid]);

        dp[end] = K[end] + max_dp_mid;
        res = max(res, dp[end]);
    }
    return res;
}
*/

// 구간 사이의 최댓값을 매번 구해야함 => 구간 최댓값을 구하는 문제(세그트리, 우선순위큐, 모노톤큐)가 포함돼 있다.
ll monotoneQueueDP() {
    ll res = -INF;
    deque<pll> deq; // {idx, dp[idx]}. 큐의 맨 앞에 가장 큰 값이 오도록 단조감소 꼴

    for (ll end = 0; end < N; end++) {
        while (!deq.empty() && deq.front().idx < end - D) 
            deq.pop_front();

        // dp[end] 계산
        dp[end] = K[end] + (deq.empty() || deq.front().dp_val < 0 ? 0 : deq.front().dp_val);
        res = max(res, dp[end]);

        while (!deq.empty() && deq.back().dp_val <= dp[end]) 
            deq.pop_back();
        
        deq.push_back({end, dp[end]});
    }

    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> N >> D;
    K.resize(N+1);
    dp.resize(N+1);
    for (ll i = 0; i < N; i++)
        cin >> K[i];

    cout << monotoneQueueDP();
    return 0;
}