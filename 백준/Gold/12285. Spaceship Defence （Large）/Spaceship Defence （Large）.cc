#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define debug(x) cout << "[debug] " << #x << " is " << x << endl
#define reg register
typedef pair<int, int> pii;
typedef pair<int, string> pis;
typedef vector<int> vint;
typedef vector<pis> vpis;
const int INF = 1e9;

int N, M, S;
unordered_map<int, string> idDB;
unordered_set<string> colors;
unordered_map<string, unordered_map<string, int>> adj;
unordered_map<string, int> visited;
unordered_map<string, int> dist;

int dijkstra(string& S, string& E) {
    visited = {}; 
    dist = {};
    for (const string& color: colors)
        dist[color] = INF;

    dist[S] = 0;
    reg priority_queue<pis, vpis, greater<pis>> pq;
    pq.push({ dist[S], S });
    while (!pq.empty()) {
        auto [_, curr] = pq.top(); pq.pop();

        if (visited[curr]) continue;
        visited[curr] = true;

        for (const auto& [next, weight]: adj[curr]) {
            if (dist[next] <= dist[curr] + weight) continue;
            dist[next] = dist[curr] + weight;
            pq.push( {dist[next], next} );
        }
    }
    return (dist[E] == INF) ? -1 : dist[E];
}

int main() {
    FASTIO;
    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        cout << "Case #" << t << ": " << endl;
        
        cin >> N;
        idDB = {};
        colors = {};
        adj = {};

        for (int i = 1; i <= N; ++i) {
            string color; cin >> color;
            idDB[i] = color;
            colors.insert(color);
        }

        cin >> M;
        for (int i = 0; i < M; ++i) {
            int a, b, cost; cin >> a >> b >> cost;
            if (idDB[a] == idDB[b]) continue;
            adj[idDB[a]][idDB[b]] = (adj[idDB[a]][idDB[b]] == 0) ? cost : min(adj[idDB[a]][idDB[b]], cost);
        }

        cin >> S;
        for (int i = 0; i < S; ++i) {
            int p, q; cin >> p >> q;
            string loc = idDB[p];
            string dest = idDB[q];
            cout << dijkstra(loc, dest) << endl;
        }
    }
    return 0;
}