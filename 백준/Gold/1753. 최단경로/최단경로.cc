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
const int MAX_V = 20000;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int V, E, K;
    cin >> V >> E >> K;
    K -= 1;

    vector<vector<P>> adj(V + 1); // 인접 리스트
    for(int i = 0; i < E; i++){
        int u, v, w;
        cin >> u >> v >> w;
        adj[u-1].push_back({v-1, w});
    }

    vector<int> dist(V + 1, INF);
    vector<bool> visited(V + 1);
    priority_queue<P, vector<P>, greater<P>> pq;

    dist[K] = 0; // 시작점 거리 초기화
    pq.push({0, K});
    while(!pq.empty()){
        int curr = pq.top().second;
        pq.pop();

        if(visited[curr]) continue;
        visited[curr] = true;
        for(P pair: adj[curr]){
            int next = pair.first, d = pair.second;
            // 거리가 갱신될 경우 PQ에 새로 넣음
            if(dist[next] > dist[curr] + d){
                dist[next] = dist[curr] + d;
                pq.push({dist[next], next});
            }
        }
    }

    for(int i = 0; i < V; i++){
        if(dist[i] == INF) cout << "INF" << endl;
        else cout << dist[i] << endl;
    }

    return 0;
}