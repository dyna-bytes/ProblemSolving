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

int N, M, K;
int S, D;
vector<pii> adj[1002];
int dist[1002][1002];

void dijkstra() {
    for (int i = 0; i <= 1000; i++)
        fill(dist[i], dist[i] + 1001, INF);

    dist[S][0] = 0;
    priority_queue<pair<int, pii>, vector<pair<int, pii>>, greater<pair<int, pii>>> pq; // { dist, { node, cnt } }

    pq.push({ 0, { S, 0 } });
    while (pq.size()) {
        auto [dist_curr, node] = pq.top(); pq.pop();
        auto [curr, cnt] = node;

        if (cnt >= N) continue;
        if (dist_curr > dist[curr][cnt]) continue;

        for (auto& [next, cost]: adj[curr]) {
            if (cnt >= N) continue;
            if (dist[next][cnt + 1] <= dist[curr][cnt] + cost) continue;
            dist[next][cnt + 1] = dist[curr][cnt] + cost;

            pq.push({ dist[next][cnt + 1], { next, cnt + 1 }});
        }
    }
}

int main() {
    FASTIO;
    cin >> N >> M >> K;
    cin >> S >> D;

    for (int i = 0; i < M; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        adj[a].push_back({ b, w });
        adj[b].push_back({ a, w });
    }
    dijkstra();


    int minDist = INF;
    for (int x = 0; x < N; x++) {
        minDist = min(minDist, dist[D][x]);
    }
    cout << minDist << endl;

    int tax = 0;
    for (int i = 0; i < K; i++) {
        int p; cin >> p;
        tax += p;

        minDist = INF;
        for (int x = 0; x < N; x++) {
            minDist = min(minDist,
                dist[D][x] + x * tax);
        }

        cout << minDist << endl;
    }

    return 0;
}