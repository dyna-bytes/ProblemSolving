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
typedef pair<ll, ll> pii;
typedef vector<ll> vll;
typedef vector<pii> vpii;

ll N;
vll trees;

ll monotoneQueueDP (ll K) {
    vll dp(N); // i 번째 위치에서의 최소 피로감
    deque<pii> deq; // deq{i, dp[i]}. dp[i]를 단조증가 꼴로 저장

    for (ll i = 0; i < N; i++) {
        while (!deq.empty() && deq.front().first < i - K)
            deq.pop_front();

        auto [prev_i, prev_dp] = (deq.empty() ? pii{0, 0} : deq.front());
        // 직전에 출발한 나무와 이번 나무의 높이를 비교해서 피로감을 1 더할지 말지 결정
        if (!deq.empty() && trees[prev_i] <= trees[i]) prev_dp++;
        dp[i] = prev_dp;

        while (!deq.empty() && deq.back().second > dp[i])
            deq.pop_back();

        while (!deq.empty() && // dp값이 같은 경우, 나무의 높이가 감소하도록 덱을 관리
        (deq.back().second == dp[i] && trees[deq.back().first] < trees[i]))
            deq.pop_back();

        deq.push_back({i, dp[i]});
    }
    return dp[N-1];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> N;
    trees.resize(N);
    for (ll i = 0; i < N; i++) cin >> trees[i];

    ll Q; cin >> Q;
    for (int i = 0; i < Q; i++) {
        int k; cin >> k;
        cout << monotoneQueueDP(k) << endl;
    }

    return 0;
}