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

ll N, M;
ll A, B, C;
vector<vector<pll>> adj;
vector<ll> dist;

bool dijkstra(ll maxCost) {
    dist.clear();
    dist.resize(N + 1, C + 1);
    priority_queue<pll, vector<pll>, greater<pll>> pq;

    dist[A] = 0;
    pq.push({ 0, A });

    while (!pq.empty()) {
        auto [dist_curr, curr] = pq.top();
        pq.pop();

        if (dist_curr > dist[curr]) continue;

        for (auto& [next, cost] : adj[curr]) {
            if (cost > maxCost) continue;
            if (dist[next] <= dist[curr] + cost) continue;

            dist[next] = dist[curr] + cost;
            pq.push({ dist[next], next });
        }
    }

    return dist[B] < C + 1;
}

int main() {
    FASTIO;
    cin >> N >> M >> A >> B >> C;
    adj.resize(N+1);
    for (int i = 0; i < M; i++) {
        ll u, v, c;
        cin >> u >> v >> c;
        adj[u].push_back({ v, c });
        adj[v].push_back({ u, c });
    }

    ll l = 0, r = C + 1;
    while (l + 1 < r) {
        ll m = (l + r)/2;
        if (dijkstra(m)) r = m;
        else l = m;
    }

    if (l + 1 == r && r == C + 1)
        cout << -1 << endl;
    else
        cout << r << endl;

    return 0;
}