#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define FASTIO cin.tie(0)->sync_with_stdio(0)

#define MAX_LOG_N 16
#define MAX_N 50005

int N, M;
int parent[MAX_N][MAX_LOG_N];
int depth[MAX_N]; // 정점의 깊이 (루트의 깊이: 0)
vector<int> adj[MAX_N];

void dfs(int curr) {
    for (int next: adj[curr]) {
        if (depth[next] != -1) continue;

        parent[next][0] = curr;
        depth[next] = depth[curr] + 1;
        dfs(next);
    }
}

int lca(int u, int v) {
    // ensure depth[u] >= detph[v]
    if (depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];

    // pull up 'u' until diff is zero.
    for (int j = 0; diff; j++) {
        if (diff % 2) u = parent[u][j];
        diff /= 2;
    }

    // u와 v의 부모가 같아 질 때까지 둘 다 위로 이동
    if (u != v) {
        for (int j = MAX_LOG_N-1; j >= 0; j--) {
            if (parent[u][j] != -1 &&
                parent[u][j] != parent[v][j])
                {
                    u = parent[u][j];
                    v = parent[v][j];
                }
        }

        u = parent[u][0];
    }

    return u;
}

int main() {
    FASTIO;

    cin >> N;
    for (int i = 0; i < N-1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    memset(parent, -1, sizeof(parent));
    memset(depth, -1, sizeof(depth));
    depth[1] = 0;

    dfs(1); // dfs로 루트부터 depth 채움

    // bottom up DP로 parent 채움
    for (int j = 0; j < MAX_LOG_N-1; j++)
        for (int i = 1; i <= N; i++)
            if (parent[i][j] != -1){
                parent[i][j+1] =
                    parent[ parent[i][j] ][j];
            }

    cin >> M;
    for (int i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        cout << lca(a, b) << endl;
    }
    return 0;
}