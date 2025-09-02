#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define FASTIO cin.tie(0)->sync_with_stdio(0)

#define endl '\n'
#define DEBUG
#ifdef DEBUG
#define debug(x) cout << #x << " is " << x << endl;
#define debugVect(v) do { \
    cout << #v << " is |" ; \
    for (auto i : v) cout << i << "|"; \
    cout << endl; \
} while (0)
#else
#define debug(x)
#define debugVect(v)
#endif

const int INF = 10000000;
typedef pair<int, int> pii;

int N, E;
int U, V;
vector<vector<pii>> adj;
vector<int> dist;
vector<bool> visited;

int dijkstra(int s, int e) {
    dist.clear();
    dist.resize(N+1, INF);
    visited.clear();
    visited.resize(N+1, false);

    priority_queue<pii> pq;
    dist[s] = 0;
    pq.push({ 0, s });

    while (pq.size()) {
        auto [ dist_curr, curr ] = pq.top(); pq.pop();
        dist_curr = -dist_curr;

        if (visited[curr]) continue;
        visited[curr] = true;

        if (curr == e) break;

        for (auto& [next, cost] : adj[curr]) {
            if (dist[next] <= dist[curr] + cost) continue;
            dist[next] = dist[curr] + cost;
            pq.push({ -dist[next], next });
        }
    }

    return dist[e];
}

int main() {
    FASTIO;
    cin >> N >> E;

    adj.resize(N+1);
    for (int i = 0; i < E; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].push_back({ b, c });
        adj[b].push_back({ a, c });
    }
    cin >> U >> V;

    int ans = dijkstra(1, U) + dijkstra(U, V) + dijkstra(V, N);
    ans = min(ans, dijkstra(1, V) + dijkstra(V, U) + dijkstra(U, N));

    if (ans >= INF) cout << -1 << endl;
    else cout << ans << endl;

    return 0;
}