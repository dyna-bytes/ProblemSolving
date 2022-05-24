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
    vector<vector<int>> reverse_adj; // rev_adj[to] = from

    Dijkstra(int n){
        N = n;
        adj.resize(N+1);
        dist.resize(N+1, INF);
        reverse_adj.resize(N+1);
    }

    void replay(int start){
        dist.clear();
        dist.resize(N+1, INF);
        run(start);
    }

    void run(int start){
        dist[start] = 0;
        priority_queue<P, vector<P>, greater<P>> pq;

        pq.push({dist[start], start});
        
        while(!pq.empty()){
            int curr = pq.top().second; pq.pop();
            if(curr == -1) continue;
            
            for(P p: adj[curr]){
                int next = p.first, weight = p.second;
                if(next == -1) continue;

                if(dist[next] > dist[curr] + weight){
                    dist[next] = dist[curr] + weight;
                    pq.push({dist[next], next});
                }
            }
        }
    }

    // 조건부 BFS
    // if (dist[u] + weight[u][v] = dist[v]) memorize path (u->v) 
    void searchShortestPath(int start){
        vector<bool> visited(N+1);
        queue<int> q;
        q.push(start);
        visited[start] = true;

        while(!q.empty()){
            int curr = q.front(); q.pop();

            for(P p: adj[curr]){
                int next = p.first, weight = p.second;

                if(dist[next] == dist[curr] + weight){
                    reverse_adj[next].push_back(curr);
                    
                    if(visited[next]) continue;
                    q.push(next);
                    visited[next] = true;
                }
            }
        }
    }

    void deleteShortestPath(int start, int dest){
        vector<bool> visited(N+1);
        queue<int> q;
        q.push(dest);
        visited[dest] = true;

        while(!q.empty()){
            int curr = q.front(); q.pop();
            if(curr == start) break;
        
            for(int next: reverse_adj[curr]){
                
                // find adj:next->curr
                for(int i = 0; i < adj[next].size(); i++){
                    int nnext = adj[next][i].first;

                    if(nnext == curr){
                        adj[next][i].first = -1;
                    }
                }
                
                if(visited[next]) continue;
                if(next != start){
                    q.push(next);
                    visited[next] = true;
                }
            }
        }
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    while(true){
        int N, M; cin >> N >> M;
        if(N == 0 && M == 0) break;
        
        int S, D; cin >> S >> D;

        Dijkstra graph(N);
        for(int i = 0; i < M; i++){
            int from, to, weight;
            cin >> from >> to >> weight;
            
            graph.adj[from].push_back({to, weight});
        }

        graph.run(S);
        graph.searchShortestPath(S);
        graph.deleteShortestPath(S, D);
        graph.replay(S);
        cout << (graph.dist[D] == INF? -1 : graph.dist[D]) << endl;
    }

    // for(int to = 0; to < graph.reverse_adj.size(); to++){
    //     for(int j = 0; j < graph.reverse_adj[to].size(); j++){
    //         debug(to);
    //         debug(graph.reverse_adj[to][j]);
    //     }
    // }
    
    return 0;
}