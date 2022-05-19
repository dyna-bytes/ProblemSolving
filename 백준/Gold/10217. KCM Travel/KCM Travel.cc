#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <climits>
#include <fstream>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define endl '\n'
typedef long long ll;
typedef pair<int, int> P;

typedef struct {
    int node;
    int cost;
    int distance;
} Node;

struct cmp{
    bool operator()(Node& n1, Node& n2){
        return n1.distance > n2.distance;
    }
};


struct Dijkstra{
    vector<vector<Node>> adj;
    vector<vector<int>> dists;
    // vector<vector<bool>> visited;
    // vector<vector<bool>> pushed;
    Dijkstra(int N, int M){
        adj.resize(N+1);
        dists.resize(N+1, vector<int>(M+1, INT_MAX));
        // visited.resize(N+1, vector<bool>(M+1));
        // pushed.resize(N+1, vector<bool>(M+1));
    }
    void run(int start = 1, int money = 10000, int N = 100){
        dists[start][money] = 0;
        priority_queue<Node, vector<Node>, cmp> pq;
        pq.push({start, money, dists[start][money]});

        while(!pq.empty()){
            Node curr = pq.top(); pq.pop();
            int n = curr.node;
            int c = curr.cost;
            int d = curr.distance;

            if(dists[n][c] < d) continue;
            dists[n][c] = d;

            if(n == N) break;

            for(Node neighbor: adj[n]){
                int next_n = neighbor.node;
                int needed_cost = neighbor.cost;
                int added_dist = neighbor.distance;
                if(c < needed_cost) continue;
                if(c == needed_cost && next_n != N) continue;
                if(dists[next_n][c - needed_cost] > dists[n][c] + added_dist){
                    dists[next_n][c - needed_cost] = dists[n][c] + added_dist;
                    pq.push({next_n, c - needed_cost, dists[next_n][c - needed_cost]});
                }
            }
        }
    }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    // ifstream fin;
    // fin.open("big2.in");

    int T; cin >> T;
    while(T--){
        int N, M, K; cin >> N >> M >> K;
        Dijkstra graph(N, M);
        for(int i = 0; i < K; i++){
            int from, to, cost, dist;
            cin >> from >> to >> cost >> dist;
            graph.adj[from].push_back({to, cost, dist});
        }

        graph.run(1, M, N);
        int ret = *min_element(graph.dists[N].begin(), graph.dists[N].end());
        
        if(ret == INT_MAX) cout << "Poor KCM" << endl;
        else cout << ret << endl;
    }
    return 0;
}