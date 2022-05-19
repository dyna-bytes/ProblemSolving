#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <climits>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define endl '\n'
typedef long long ll;
typedef pair<ll, ll> P;

typedef struct {
    ll dist;
    P node; // {N, K}
} Node;

struct cmp {
    bool operator()(Node& n1, Node& n2){
        return n1.dist > n2.dist;
    }
};

struct Dijkstra{
    vector<vector<P>> adj;
    vector<vector<ll>> dist; // node(u, k)의 거리 정보. N * K 크기의 이차원 배열
    vector<vector<bool>> visited;
    Dijkstra(ll n, ll k){
        adj.resize(n + 1);
        dist.resize(n + 1, vector<ll>(k + 1, LONG_LONG_MAX));
        visited.resize(n + 1, vector<bool>(k + 1));
    }
    void run(ll start = 1, ll k = 20){
        dist[start][k] = 0;
        priority_queue<Node, vector<Node>, cmp> pq;
        pq.push({dist[start][k], {start, k}});

        while(!pq.empty()){
            Node curr = pq.top();
            pq.pop();

            ll n = curr.node.first;
            ll k = curr.node.second;

            if(visited[n][k]) continue;
            visited[n][k] = true;

            for(P p: adj[n]){
                ll next_n = p.first;
                ll cost = p.second;

                if(dist[next_n][k] > dist[n][k] + cost){
                    dist[next_n][k] = dist[n][k] + cost;
                    pq.push({dist[next_n][k], {next_n, k}});
                }

                if(k > 0 && dist[next_n][k-1] > dist[n][k]){
                    dist[next_n][k-1] = dist[n][k];
                    pq.push({dist[next_n][k-1], {next_n, k-1}});
                }
            }
        }
    }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll N, M, K;
    cin >> N >> M >> K;
    Dijkstra graph(N, K);

    for(ll i = 0; i < M; i++){
        ll from, to, cost;
        cin >> from >> to >> cost;
        graph.adj[from].push_back({to, cost});
        graph.adj[to].push_back({from, cost});
    }

    graph.run(1, K);

    ll ret = LONG_LONG_MAX;
    for(ll k = 0; k <= K; k++){
        ret = min(ret, graph.dist[N][k]);
    }
    cout << ret;

    return 0;
}