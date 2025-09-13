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
typedef pair<int, pii> pipii;
const int INF = 1e9;
const int MAX_N = 101;
const int MAX_M = 10001;

vector<pipii> adj[MAX_N];
int D[MAX_N][MAX_M]; // { node, cost }
int solution(int N, int M, int K) {
    priority_queue<pipii, vector<pipii>, greater<pipii>> pq; // { dist, { node, cost }}
    D[1][0] = 0;
    pq.push({ 0, { 1, 0 }});

    while (pq.size()) {
        auto [ dist_curr, node ] = pq.top(); pq.pop();
        auto [ curr, cost_sum ] = node;

        if (dist_curr > D[curr][cost_sum]) continue;

        debug(curr);
        debug(dist_curr);
        debug(cost_sum);

        for (auto& [ next, cost_dist ]: adj[curr]) {
            auto& [ cost, dist ] = cost_dist;

            if (cost_sum + cost > M) continue;
            if (D[next][cost_sum + cost] <= dist_curr + dist) continue;

            for (int c = cost_sum + cost; c <= M; c++) {
                if (D[next][c] > dist_curr + dist)
                    D[next][c] = dist_curr + dist;
                else
                    break;
            }

            pq.push({ D[next][cost_sum + cost], { next, cost_sum + cost }});
        }
    }

    return *min_element(D[N], D[N] + M + 1);
}

int main() {
    FASTIO;
    int T; cin >> T;

    while (T--) {
        int N, M, K;
        cin >> N >> M >> K;

        for (int i = 1; i <= N; ++i)
            fill(D[i], D[i] + M + 1, INF);

        for (int i = 0; i < K; i++) {
            int u, v, c, d;
            cin >> u >> v >> c >> d;
            adj[u].push_back({ v, { c, d } });
        }
        for (auto& arrow: adj) {
            sort(arrow.begin(), arrow.end(), [](pipii& a, pipii& b) {
                auto [_, cost_dist_a] = a;
                auto [__, cost_dist_b] = b;
                return cost_dist_a.first > cost_dist_b.first;
            });
        }

        int ret = solution(N, M, K);
        if (ret >= INF) cout << "Poor KCM" << endl;
        else cout << ret << endl;

        for (int i = 1; i <= N; i++)
            adj[i].clear();
    }

    return 0;
}