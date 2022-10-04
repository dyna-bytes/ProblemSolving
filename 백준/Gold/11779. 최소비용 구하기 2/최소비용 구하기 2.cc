#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef pair<int, int> pii;
typedef vector<int> vint;
typedef vector<pii> vpii;
const int INF = 1e9 + 1;

struct Dijkstra {
    int N;
    vector<vpii> adj;
    vint dist;
    vint prev;
    vint visited;

    Dijkstra(int n) {
        N = n;
        adj.resize(N+1);
        dist.resize(N+1, INF);
        prev.resize(N+1, -1);
        visited.resize(N+1);
    }
    void setAdj(int from, int to, int weight) {
        adj[from].push_back({to, weight});
    }
    int getDist(int target) {
        return dist[target];
    }
    void run(int start) {
        dist[start] = 0;

        priority_queue<pii, vpii, greater<pii>> pq;
        pq.push({dist[start], start});

        while (!pq.empty()) {
            auto [_, curr] = pq.top(); pq.pop();

            if (visited[curr]) continue;
            visited[curr] = true;

            for (auto [next, weight]: adj[curr]) {
                if (dist[next] < dist[curr] + weight) continue;

                dist[next] = dist[curr] + weight;
                prev[next] = curr;
                pq.push({dist[next], next});
            }
        }
    }
    void backtracking(int S, int E) {
        vint path;
        for (int curr = E; curr != S; curr = prev[curr])
            path.push_back(curr);

        path.push_back(S);
        reverse(path.begin(), path.end());

        cout << path.size() << endl;
        for (int elem: path) cout << elem << " ";
    }
};

int main() {
    int N, M;
    cin >> N >> M;
    Dijkstra Graph(N);
    for (int i = 0; i < M; i++) {
        int from, to, weight;
        cin >> from >> to >> weight;
        Graph.setAdj(from, to, weight);
    }

    int S, E;
    cin >> S >> E;
    Graph.run(S);

    cout << Graph.getDist(E) << endl;
    Graph.backtracking(S, E);
    return 0;
}