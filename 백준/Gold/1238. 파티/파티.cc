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
const int INF = 1000000000;

struct Dijkstra{
    int N;
    vector<vector<P>> adj;
    Dijkstra(int n){
        N = n;
        adj.resize(N+1);
    }
    void addAdj(int from, int to, int dist){
        adj[from].push_back({to, dist});
    }
    void run(int S, int E, vector<int>& dist, bool to_centroid){
        vector<bool> visited(N+1);
        priority_queue<P, vector<P>, greater<P>> pq;
        dist[S] = 0;

        pq.push({dist[S], S});
        while (!pq.empty()){
            int curr = pq.top().second; pq.pop();

            if(to_centroid && curr == E) break;
            if(visited[curr]) continue;
            visited[curr] = true;
            for(P p: adj[curr]){
                int next = p.first, weight = p.second;
                if(dist[next] > dist[curr] + weight){
                    dist[next] = dist[curr] + weight;
                    pq.push({dist[next], next});
                }
            }
        }
    }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N, M, X;
    cin >> N >> M >> X;
    Dijkstra Graph(N);

    for(int i = 0; i < M; i++){
        int from, to, dist;
        cin >> from >> to >> dist;
        Graph.addAdj(from, to, dist);
    }

    vector<int> time(N+1, INF);
    // get time for "X -> all nodes"
    Graph.run(X, -1, time, false);

    // get time for "all nodes -> X"
    for(int n = 1; n <= N; n++){
        vector<int> time_NtoX(N+1, INF);
        Graph.run(n, X, time_NtoX, true);

        time[n] += time_NtoX[X];
    }

    cout << *max_element(&time[1], &time[N+1]);
    return 0;
}