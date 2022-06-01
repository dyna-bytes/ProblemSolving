#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define endl '\n'
typedef long long ll;
typedef pair<int, int> P;
const int INF = 10000000;

struct Dijkstra{
    int N;
    vector<vector<P>> adj;
    vector<int> dist;
    vector<bool> visited;
    Dijkstra(int n){
        N = n;
        adj.resize(N+1);
    }
    void init(){
        dist.clear();
        visited.clear();
        dist.resize(N+1, INF);
        visited.resize(N+1);
    }
    void addAdj(int from, int to, int dist){ adj[from].push_back({to, dist}); }
    int run(int S, int E){
        init();
        dist[S] = 0;
        priority_queue<P, vector<P>, greater<P>> pq;
        pq.push({dist[S], S});

        while(!pq.empty()){
            int curr = pq.top().second; pq.pop();
            if(visited[curr]) continue;
            visited[curr] = true;

            if(curr == E) break;

            for(P p: adj[curr]){
                int next = p.first, weight = p.second;
                if(dist[next] > dist[curr] + weight){
                    dist[next] = dist[curr] + weight;
                    // debug(dist[next]);
                    pq.push({dist[next], next});
                }
            }
        }
        return dist[E];
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N, E; cin >> N >> E;
    Dijkstra Graph(N);

    for(int i = 0; i < E; i++){
        int from, to, dist;
        cin >> from >> to >> dist;
        Graph.addAdj(from, to, dist);
        Graph.addAdj(to, from, dist);
    }

    int A, B; cin >> A >> B;

    // 경로: 1 -> A -> B -> N;
    int ret = Graph.run(1, A) + Graph.run(A, B) + Graph.run(B, N);

    // // 경로: 1 -> B -> A -> N;
    ret = min(ret, Graph.run(1, B) + Graph.run(B, A) + Graph.run(A, N));

    if(ret >= INF) cout << -1;
    else cout << ret;
    return 0;
}