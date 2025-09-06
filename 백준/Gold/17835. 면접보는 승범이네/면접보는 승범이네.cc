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
const ll INF = 1e12;
typedef pair<ll, ll> pll;

int N, M, K;
vector<vector<pll>> adj;
vector<ll> dist;
vector<bool> visited;
priority_queue<pll, vector<pll>, greater<pll>> pq;

void dijkstra() {
    while (!pq.empty()) {
        auto [dist_curr, curr] = pq.top();
        pq.pop();

        if (dist_curr > dist[curr]) continue;

        for (auto& [next, weight]: adj[curr]) {
            if (dist[next] <= dist[curr] + weight) continue;

            dist[next] = dist[curr] + weight;
            pq.push({ dist[next], next });
        }
    }
}

int main() {
    FASTIO;
    cin >> N >> M >> K;
    adj.resize(N+1);

    for (int i = 0; i < M; i++) {
        int from, to, cost;
        cin >> from >> to >> cost;

        swap(from, to);
        adj[from].push_back({ to, cost });
    }

    dist.resize(N+1, INF);
    visited.resize(N+1, false);

    int target;
    for (int i = 0; i < K; i++) {
        cin >> target;
        dist[target] = 0;
        pq.push({ 0, target });
    }

    dijkstra();

    ll maxDist = 0;
    for (int i = 1; i <= N; i++) {
        if (maxDist < dist[i]) {
            maxDist = dist[i];
            target = i;
        }
    }
    cout << target << endl;
    cout << maxDist << endl;
    debugVect(dist);

    return 0;
}