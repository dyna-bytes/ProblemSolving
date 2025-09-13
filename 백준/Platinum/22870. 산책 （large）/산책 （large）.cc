#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define FASTIO cin.tie(0)->sync_with_stdio(0)

#define endl '\n'
// #define DEBUG
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

typedef pair<int, int> pii;
const int INF = 1e9;

int N, M;
vector<vector<pii>> adj;
vector<int> dist;
vector<int> nexts;
vector<bool> visited;

int dijkstra(int s, int e) {
    dist.clear();
    dist.resize(N+1, INF);

    priority_queue<pii, vector<pii>, greater<pii>> pq;
    dist[s] = 0;
    pq.push({ 0, s });
    while (pq.size()) {
        auto [dist_curr, curr] = pq.top(); pq.pop();

        if (dist_curr > dist[curr]) continue;

        debug("--------");
        debug(curr);

        for (auto& [next, cost]: adj[curr]) {
            if (visited[next]) continue;
            if (dist[next] <= dist[curr] + cost) continue;

            dist[next] = dist[curr] + cost;
            pq.push({ dist[next], next });
        }
    }

    return dist[e];
}

void bfs(int s, int e) {
    queue<int> q;
    q.push(e);

    while (q.size()) {
        int curr = q.front(); q.pop();

        for (auto [prev, cost]: adj[curr]) {
            if (dist[curr] == dist[prev] + cost &&
                nexts[prev] > curr) {
                nexts[prev] = curr;
                q.push(prev);
            }
        }
    }

    for (int curr = s; curr != e; curr = nexts[curr])
        if (curr != e && curr != s)
            visited[curr] = true;
}

int main() {
    FASTIO;
    cin >> N >> M;
    adj.resize(N+1);
    nexts.resize(N+1, N+1);
    visited.resize(N+1, false);

    for (int i = 0; i < M; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].push_back({ b, c });
        adj[b].push_back({ a, c });
    }

    int S, E;
    cin >> S >> E;

    int ret = dijkstra(S, E);
    debug(ret);

    bfs(S, E);

    ret += dijkstra(E, S);
    cout << ret << endl;
    return 0;
}