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
const int INF = 1e9;

vint cost;
vint psum;
vector<vint> dp;
// 구간 [s, e)의 최소 비용
int minCostSum(int s, int e) {
    if (s + 1 == e) return cost[s];

    int& ret = dp[s][e];
    if (ret != -1) return ret;
    ret = INF;

    for (int m = s + 1; m < e; m++) {
        int left = (m > s + 1)? (psum[m] - psum[s]) + minCostSum(s, m) : minCostSum(s, m);
        int right = (e > m + 1)? (psum[e] - psum[m]) + minCostSum(m, e) : minCostSum(m, e);
        ret = min(ret, left + right);
    }
    
    return ret;
}

void solve() {
    int K; cin >> K;
    cost.clear(), cost.resize(K);
    psum.clear(), psum.resize(K+1);
    dp.clear(), dp.resize(K+2, vint(K+2, -1));
    
    for (int i = 0; i < K; i++) {
        cin >> cost[i];
        psum[i+1] = psum[i] + cost[i];
    }
    cout << minCostSum(0, K) << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int T; cin >> T;
    while (T--) solve();   
    return 0;
}