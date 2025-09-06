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

typedef long long ll;
typedef pair<ll, ll> pll;

ll N, M, K;
vector<vector<pll>> adj;
vector<vector<ll>> dist;

ll dijkstra() {
    priority_queue<pair<ll, pll>,
        vector<pair<ll, pll>>, greater<pair<ll, pll>>> pq;

    dist.resize(N+1, vector<ll>(K+1, LONG_LONG_MAX));
    int start = 1;
    dist[start][K] = 0;
    pq.push({ dist[start][K], { start, K } });
    while (!pq.empty()) {
        auto [dist_curr, node] = pq.top(); pq.pop();
        auto [curr, k] = node;

        if (dist_curr > dist[curr][k]) continue;

        for (auto& [next, cost]: adj[curr]) {
            if (k > 0 && dist[next][k-1] > dist[curr][k]) {
                    dist[next][k-1] = dist[curr][k];
                    pq.push({ dist[next][k-1], { next, k-1 } });
            }

            if (dist[next][k] > dist[curr][k] + cost) {
                dist[next][k] = dist[curr][k] + cost;
                pq.push({ dist[next][k], { next, k } });
            }
        }
    }

    ll minDist = LONG_LONG_MAX;
    for (int k = 0; k <= K; k++)
        minDist = min(minDist, dist[N][k]);
    return minDist;
}

int main() {
    FASTIO;

    cin >> N >> M >> K;
    adj.resize(N+1);
    for (int i = 0; i < M; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        adj[u].push_back({ v, c });
        adj[v].push_back({ u, c });
    }

    cout << dijkstra() << endl;
    return 0;
}