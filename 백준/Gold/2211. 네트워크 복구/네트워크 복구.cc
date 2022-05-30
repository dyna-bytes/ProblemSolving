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
    vector<int> dist;
    vector<int> prev;
    Dijkstra(int n){
        N = n;
        adj.resize(N+1);
        dist.resize(N+1, INF);
        prev.resize(N+1, -1);
    }
    void setAdj(int from, int to, int weight){
        adj[from].push_back({to, weight});
        adj[to].push_back({from, weight});
    }
    void run(int S = 1){
        vector<bool> visited(N+1);
        priority_queue<P, vector<P>, greater<P>> pq;

        dist[S] = 0;
        pq.push({dist[S], S});
        while(!pq.empty()){
            int curr = pq.top().second; pq.pop();
            if(visited[curr]) continue;
            visited[curr] = true;

            for(P p: adj[curr]){
                int next = p.first, weight = p.second;
                if(dist[next] > dist[curr] + weight){
                    dist[next] = dist[curr] + weight;
                    prev[next] = curr;
                    pq.push({dist[next], next});
                }
            }
        }
    }

    void rebuild(){
        cout << N-1 << endl; // N개의 노드가 있는 그래프: N-1개의 간선 MST 
        for(int here = 1; here <= N; here++){
            if(prev[here] == -1) continue;
            cout << here << " " << prev[here] << endl;
        }
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N, M; cin >> N >> M;
    Dijkstra Graph(N);
    for(int i = 0; i < M; i++){
        int from, to, weight;
        cin >> from >> to >> weight;
        Graph.setAdj(from, to, weight);
    }
    Graph.run();
    Graph.rebuild();
    return 0;
}