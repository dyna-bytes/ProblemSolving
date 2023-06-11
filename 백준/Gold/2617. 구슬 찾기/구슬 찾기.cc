#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vint;
typedef vector<ll> vll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;

#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#define endl '\n';
#define debug(x) cout << "[Debug] " << #x << " is " << x << endl;
#define _debugV1(v) for (auto it = v.begin(); it != v.end(); ++it) { cout << *it; if (next(it) != v.end()) cout << " | "; }
#define debugVec(v) do { \
    cout << "[Debug] [ "; \
    _debugV1(v); \
    cout << " ]" << endl; \
} while (0)
#define debugV2(v) do { \
    cout << "[Debug] [" << endl; \
    for (auto v1: v) { \
        cout << "  [ "; \
        _debugV1(v1); \
        cout << " ]" << endl; \
    } \
    cout << "]" << endl; \
} while (0)
#define pair_out(pair) { out << '{' << pair.first << ", " << pair.second << '}'; }
std::ostream& operator << (ostream& out, pii& pair) {
    pair_out(pair);
    return out;
}
std::ostream& operator << (ostream& out, pll& pair) {
    pair_out(pair);
    return out;
}

int N, M;
vector<vint> adj, rev_adj; 
vint visited;
vint res;

int dfs(int curr, vector<vint> &adj) {
    int sum = 1;

    for (int next: adj[curr]) {
        if (visited[next]) continue;
        visited[next] = true;
        sum += dfs(next, adj);
    }
    return sum;
}

int main() {
    FASTIO;
    cin >> N >> M;
    adj = rev_adj = vector<vint>(N + 1);
    visited = vint(N + 1);
    res = vint(N + 1);

    for (int i = 0; i < M; i++) {
        int u, v; 
        cin >> u >> v;
        adj[v].push_back(u);
        rev_adj[u].push_back(v);
    }

    for (int i = 1; i <= N; i++) {
        visited = vint(N + 1, 0);
        visited[i] = true;
        if (dfs(i, adj) > (N + 1)/2) res[i]++;
    }

    for (int i = 1; i <= N; i++) {
        visited = vint(N + 1, 0);
        visited[i] = true;
        if (dfs(i, rev_adj) > (N + 1)/2) res[i]++;
    }

    int cnt = 0;
    for (int i = 1; i <= N; i++) 
        if (res[i]) cnt++;

    cout << cnt;
    
    return 0;
}