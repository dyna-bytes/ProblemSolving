#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
typedef vector<int> vint;
typedef vector<pii> vpii;
const int INF = 1e9 + 1;

vint dijkstra(int N, vector<vpii>& adj, int start) {
    vint dist(N+1, INF);
    vint visited(N+1);

    priority_queue<pii, vpii, greater<pii>> pq;
    dist[start] = 0;
    pq.push({dist[start], start});

    while (!pq.empty()) {
        auto [_, curr] = pq.top(); pq.pop();

        if (visited[curr]) continue;
        visited[curr] = true;

        for (auto [next, weight]: adj[curr]) {
            if (dist[next] <= dist[curr] + weight) continue;
            dist[next] = dist[curr] + weight;
            pq.push({dist[next], next});
        }
    }

    return dist;
}

void solve() {
    int N, M, T; cin >> N >> M >> T;
    int s, g, h; cin >> s >> g >> h;

    int g_to_h = 0;
    vector<vpii> adj(N+1);
    for (int i = 0; i < M; i++) {
        int from, to, weight; cin >> from >> to >> weight;
        adj[from].push_back({to, weight});
        adj[to].push_back({from, weight});
        if ((from == g && to == h) || (from == h && to == g)) g_to_h = weight;
    }

    vint destinations(T);
    for (int i = 0; i < T; i++) cin >> destinations[i];

    vint dist_straight = dijkstra(N, adj, s);
    int s_to_g = dist_straight[g];
    int s_to_h = dist_straight[h];

    // s -> g -> h -> dest
    vint dist_via1 = dijkstra(N, adj, h);
    for (int dest: destinations)
        dist_via1[dest] += min(s_to_g + g_to_h, INF);

    // s -> h -> g -> dest
    vint dist_via2 = dijkstra(N, adj, g);
    for (int dest: destinations)
        dist_via2[dest] += min(s_to_h + g_to_h, INF);

    vint ans;
    for (int dest: destinations) {
        if (dist_straight[dest] == INF) continue;
        if (dist_via1[dest] == dist_straight[dest] || dist_via2[dest] == dist_straight[dest])
            ans.push_back(dest);
    }

    sort(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); ++i) cout << ans[i] << ' ';
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int T; cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}