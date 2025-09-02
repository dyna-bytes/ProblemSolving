#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define FASTIO cin.tie(0)->sync_with_stdio(0)

#define endl '\n'
typedef pair<int, int> pii;
const int INF = 1e9;

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

void solution(int V, int E, int K, vector<vector<pii>>& adj, vector<int>& dist) {
    dist.resize(V+1, INF);
    priority_queue<pii, vector<pii>, greater<pii>> pq; // { cost, node }

    dist[K] = 0;
    pq.push({ 0, K });
    while (!pq.empty()) {
        auto [dist_curr, curr] = pq.top();
        pq.pop();

        if (dist_curr > dist[curr]) continue;

        for (auto& [neighbor, cost] : adj[curr]) {
            if (dist[neighbor] <= dist[curr] + cost) continue;

            dist[neighbor] = dist[curr] + cost;
            pq.push({ dist[neighbor], neighbor });
        }
    }
}

int main() {
    FASTIO;

    int V, E, K;
    vector<vector<pii>> adj;
    vector<int> dist;

    cin >> V >> E >> K;
    adj.resize(V + 1);

    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ v, w });
    }

    solution(V, E, K, adj, dist);

    for (int i = 1; i <= V; i++){
        if (dist[i] == INF) cout << "INF" << endl;
        else cout << dist[i] << endl;
    }

    return 0;
}