#include <bits/stdc++.h>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define debugVec(v) do { \
    std::cout << "[Debug] ["; \
    for(int i = 0; i < ((v.size())-1); i++) std::cout << v[i] << "|"; \
    std::cout << v[((v.size())-1)] << "]\n"; \
} while(0)
#define debugV2D(v) do { \
    std::cout << "[Debug] [\n"; \
    for(int y = 0; y < (v.size()); y++) { \
        if(v[y].empty()){ std::cout << "  []\n"; continue; } \
        std::cout << "  ["; \
        for(int x = 0; x < ((v[y].size())-1); x++) \
            std::cout << v[y][x] << "|"; \
        std::cout << v[y][(v[y].size())-1] << "]\n"; \
    } \
    std::cout << "]\n"; \
} while(0)
#define endl '\n'
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vint;
typedef vector<pii> vpii;
const int INF = 1e9;

vector<vpii> adj;
vint visited;
vint dist;

int dijkstra(int start, int V, int E) {
    visited.clear(), visited.resize(V+1);
    dist.clear(), dist.resize(V+1, INF);
    priority_queue<pii, vpii, greater<pii>> pq;

    dist[start] = 0;
    pq.push({dist[start], start});
    bool first_time_then_pass = true;

    while (!pq.empty()) {
        auto [curr_dist, curr] = pq.top(); pq.pop();

        if (curr == start) {
            if (first_time_then_pass) first_time_then_pass = false;
            else return curr_dist;
        }

        if (visited[curr]) continue;
        visited[curr] = true;

        for (auto [next, weight]: adj[curr]) {
            if (next == start || dist[next] > dist[curr] + weight) {
                dist[next] = dist[curr] + weight;
                pq.push({dist[next], next});
            }
        }
    }

    return INF;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int V, E; cin >> V >> E;
    adj.resize(V+1);
    
    for (int i = 0; i < E; i++) {
        int from, to, weight;
        cin >> from >> to >> weight;
        adj[from].push_back({to, weight});
    }

    int res = INF;
    for (int start = 1; start <= V; start++)
        res = min(res, dijkstra(start, V, E));

    if (res == INF) cout << -1;
    else cout << res;
    return 0;
}