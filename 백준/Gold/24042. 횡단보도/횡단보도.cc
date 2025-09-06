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
const ll INF = 7e10 + 1;

ll N, M;
vector<vector<pll>> adj;
vector<ll> dist;

ll dijkstra() {
    dist.resize(N+1, INF);
    priority_queue<pll, vector<pll>, greater<pll>> pq;

    int start = 1;
    dist[start] = 0;
    pq.push( {0, start} );

    while(!pq.empty()) {
        auto [dist_curr, curr] = pq.top();
        pq.pop();

        if (dist_curr > dist[curr]) continue;

        for (auto& [next, i]: adj[curr]) {
            ll cost = (((i - dist_curr) % M) + M) % M;
            debug(cost);
            if (dist[next] <= dist[curr] + cost) continue;

            dist[next] = dist[curr] + cost;
            pq.push({ dist[next], next });
        }
    }

    return 1 + dist[N];
}

int main() {
    FASTIO;
    cin >> N >> M;
    adj.resize(N+1);
    for (int i = 0; i < M; i++) {
        int A, B;
        cin >> A >> B;
        adj[A].push_back({ B, i });
        adj[B].push_back({ A, i });
    }
    cout << dijkstra() << endl;
    return 0;
}