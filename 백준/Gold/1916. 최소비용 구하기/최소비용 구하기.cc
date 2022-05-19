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
    vector<vector<P>> adj;
    vector<int> dist;
    vector<bool> visited;
    Dijkstra(int N){
        adj.resize(N + 1);
        dist.resize(N + 1, INF);
        visited.resize(N + 1);
    }
    void setAdj(int from, int to, int weight){
        adj[from].push_back({to, weight});
        // 인접 리스트에 담을 때는 {노드, 가중치} 순으로 담지만
        // 뒤에 우선순위 큐에서는 {가중치, 노드} 순으로 담음(가중치에 대해 오름차순 정렬해야 하므로)
    }
    int getDist(int target){
        return dist[target];
    }
    void run(int start){
        dist[start] = 0;

        priority_queue<P, vector<P>, greater<P>> pq;
        pq.push({dist[start], start});

        while(!pq.empty()){
            int curr = pq.top().second;
            pq.pop();

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
    
    int N, M;
    cin >> N >> M;
    Dijkstra graph(N);

    for(int i = 0; i < M; i++){
        int from, to, weight;
        cin >> from >> to >> weight;
        graph.setAdj(from, to, weight);
    }

    int start, end;
    cin >> start >> end;

    graph.run(start);
    cout << graph.getDist(end);
    
    return 0;
}