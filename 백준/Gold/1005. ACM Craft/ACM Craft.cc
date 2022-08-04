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
typedef pair<int, int> pii;
typedef vector<int> vint;
typedef vector<pii> vpii;
#define NOT !

int N, K, W;
vint time_(1000);
vint dp(1000);
vector<vint> adj(1000);

// 현재 건물에서부터 위상정렬해서 끝까지 방문 가능한 모든 노드들의 건설 시간 총합
int dfs(int curr) {
    int& ret = dp[curr];
    if (ret != -1) return ret;

    ret = time_[curr];
    for (int next: adj[curr]) 
        ret = max(ret, time_[curr] + dfs(next));
    
    return ret;
}

void solve() {
    cin >> N >> K;

    time_.clear();
    dp.clear();
    adj.clear();

    time_.resize(N);
    dp.resize(N, -1);
    adj.resize(N);

    for (int i = 0; i < N; i++) cin >> time_[i];
    for (int i = 0; i < K; i++) {
        int X, Y; cin >> X >> Y; 
        X--, Y--;
        adj[Y].push_back(X); // adj 관계를 거꾸로 넣어줌
    }
    cin >> W; 
    W--;

    cout << dfs(W) << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int T; cin >> T;
    while (T--) solve();
    
    return 0;
}