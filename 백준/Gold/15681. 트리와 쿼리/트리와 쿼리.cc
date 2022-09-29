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

vector<vint> adj;
vint dp;
vint visited;

int dfs(int curr) {
    int& ret = dp[curr];
    if (ret != -1) return ret;

    ret = 1;
    visited[curr] = true;
    for (int next: adj[curr]) {
        if (visited[next]) continue;
        ret += dfs(next);
    }
    return ret;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int N, R, Q;
    cin >> N >> R >> Q;
    adj.resize(N);
    visited.resize(N);
    dp.resize(N, -1);

    for (int i = 0; i < N-1; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    R--;
    dfs(R);

    for (int i = 0; i < Q; i++) {
        int r; cin >> r;
        r--;
        cout << dfs(r) << endl;
    }
    return 0;
}