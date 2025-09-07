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

typedef long long ll;
typedef pair<ll, ll> pll;
const ll INF = 1e9;

ll N, M, K;
vector<vector<pll>> adj;
vector<priority_queue<ll>> dist;

void dijkstra(int start = 1) {
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    dist[start].push(0);
    pq.push({ 0, start });

    while (pq.size()) {
        auto [dist_curr, curr] = pq.top();
        pq.pop();

        for (auto& [next, cost]: adj[curr]) {
            if (dist[next].size() < K) {
                dist[next].push(dist_curr + cost);
                pq.push({ dist_curr + cost, next });
            } else if (dist[next].top() > dist_curr + cost) {
                dist[next].pop();
                dist[next].push(dist_curr + cost);
                pq.push({ dist_curr + cost, next });
            }
        }
    }
}

int main() {
    FASTIO;

    cin >> N >> M >> K;
    adj.resize(N+1);
    dist.resize(N+1);
    for (int i = 0; i < M; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        adj[u].push_back({ v, c });
    }

    dijkstra();

    for (int i = 1; i <= N; i++) {
        debug(i);
        debug(dist[i].size());
        if (dist[i].size() != K) cout << -1 << endl;
        else cout << dist[i].top() << endl;
    }

    return 0;
}