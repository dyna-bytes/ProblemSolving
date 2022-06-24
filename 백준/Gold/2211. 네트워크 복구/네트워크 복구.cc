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
        std::cout << "  ["; \
        for(int x = 0; x < ((v[y].size())-1); x++) \
            std::cout << v[y][x] << "|"; \
        std::cout << v[y][(v[y].size())-1] << "]\n"; \
    } \
    std::cout << "]\n"; \
} while(0)
#define endl '\n'
typedef long long ll;
typedef pair<int, int> P;
const int INF = 1e9 + 1;

struct Dijkstra{
    int N;
    vector<vector<P>> adj; // adjacent list
    vector<int> dist; // dist from start
    vector<int> prev; // memorize the path from start
    vector<bool> visited;
    Dijkstra(int n){
        N = n;
        adj.resize(N+1);
        dist.resize(N+1, INF);
        prev.resize(N+1, -1);
        visited.resize(N+1);
    }
    void setAdj(int from, int to, int weight){
        adj[from].push_back({to, weight});
        adj[to].push_back({from, weight}); // 양 방향 간선인 경우
    }
    int getDist(int target){ return dist[target]; }
    void run(int start){
        // 문제에 따라 visited, prev를 초기화 해야 하는지 확인하고 사용
        // visited.clear(); visited.resize(N+1);
        dist[start] = 0;

        priority_queue<P, vector<P>, greater<P>> pq; // ascending sort by dist
        pq.push({dist[start], start});
        while(!pq.empty()){
            int curr = pq.top().second; pq.pop();

            if (visited[curr]) continue;
            visited[curr] = true;

            for(P p: adj[curr]){
                int next = p.first, weight = p.second;

                if (dist[next] > dist[curr] + weight) {
                    dist[next] = dist[curr] + weight;
                    prev[next] = curr;
                    pq.push({dist[next], next});
                }
            }
        }
    }
    void show_MST(){
        cout << N-1 << endl;
        for(int here = 1; here <= N; here++){
            if (prev[here] == -1) continue;
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
    Graph.run(1);
    Graph.show_MST();
    return 0;
}