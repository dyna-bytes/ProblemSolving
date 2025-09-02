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

const int INF = 1e9;
typedef pair<int, int> pii;

vector<int> dist;
vector<bool> visited;

int dijkstra(int S, int E, vector<vector<pii>>& adj) {
    dist.clear();
    dist.resize(adj.size(), INF);
    visited.clear();
    visited.resize(adj.size(), false);

    priority_queue<pii, vector<pii>, greater<pii>> pq;
    dist[S] = 0;
    pq.push({ 0, S });

    while (pq.size()) {
        auto [_, curr] = pq.top();
        pq.pop();

        if (visited[curr]) continue;
        visited[curr] = true;

        for (auto& [next, cost] : adj[curr]) {
            if (dist[next] < dist[curr] + cost) continue;

            dist[next] = dist[curr] + cost;
            pq.push({ dist[next], next });
        }
    }

    return dist[E];
}

int solution(int N, int M, int X, vector<vector<pii>>& adj) {
    vector<int> returns;

    dijkstra(X, 0, adj);
    returns = dist;

    for (int i = 1; i <= N; i++) {
        if (i == X) continue;
        returns[i] += dijkstra(i, X, adj);
    }

    debugVect(returns);
    return *max_element(returns.begin() + 1, returns.end());
}

int main() {
    int N, M, X;
    vector<vector<pii>> adj;

    cin >> N >> M >> X;
    adj.resize(N+1);

    for (int i = 0; i < M; i++) {
        int S, E, T;
        cin >> S >> E >> T;
        adj[S].push_back({ E, T });
    }

    cout << solution(N, M, X, adj) << endl;

    return 0;
}