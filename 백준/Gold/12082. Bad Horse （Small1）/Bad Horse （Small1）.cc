#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define debug(x) cout << "[debug] " << #x << " is " << x << endl
typedef vector<int> vint;
#define MAXN 21
int N;
int M;
map<string, int> nodes;
vint adj[MAXN];
int visited[MAXN];

int dfs(int curr, int color) {
    visited[curr] = color;

    int ret = false;
    for (int next: adj[curr]) {
        if (visited[next] == color) return true;

        if (!visited[next])
            ret += dfs(next, -color);
    }
    return ret;
}
void solve() {
    cin >> M;
    N = 0;
    nodes = {};
    for (int i = 0; i < MAXN; i++) adj[i] = {};
    memset(visited, 0, sizeof(visited));

    for (int i = 0; i < M; i++) {
        string A, B;
        cin >> A >> B;
        if (nodes[A] == 0) nodes[A] = ++N;
        if (nodes[B] == 0) nodes[B] = ++N;
        
        adj[nodes[A]].push_back(nodes[B]);
        adj[nodes[B]].push_back(nodes[A]);
    }

    int ret = 0;
    for (int n = 1; n <= N; n++) {
        if (visited[n]) continue;
        ret += dfs(n, 1);
    }
    cout << (ret ? "No" : "Yes") << endl;
}
int main() {
    FASTIO;
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}