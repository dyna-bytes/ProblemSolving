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

const int INF = 1e9;
typedef pair<int, int> pii;
typedef long long ll;
typedef pair<ll, ll> pll;

int N, M;
int S, E;
vector<vector<pll>> adj;
vector<ll> dist;
vector<bool> visited;

int solution(int s, int e) {
    dist.resize(N+1, INF);
    visited.resize(N+1, false);

    priority_queue<pll, vector<pll>, greater<pll>> pq;
    dist[s] = 0;
    pq.push( { 0, s });

    while (pq.size()) {
        auto [_, curr] = pq.top();
        pq.pop();

        if (visited[curr]) continue;
        visited[curr] = true;

        for (auto& [next, cost] : adj[curr]) {
            if (dist[next] <= dist[curr] + cost) continue;
            dist[next] = dist[curr] + cost;
            pq.push({ dist[next], next });
        }
    }

    return dist[e];
}

int main() {
    FASTIO;
    cin >> N >> M;

    adj.resize(N+1);
    for (int i = 0; i < M; i++) {
        int from, to, dist;
        cin >> from >> to >> dist;
        adj[from].push_back({ to, dist });
    }

    cin >> S >> E;
    cout << solution(S, E) << endl;

    return 0;
}