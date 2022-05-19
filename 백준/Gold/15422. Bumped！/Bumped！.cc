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
typedef pair<ll, ll> P;
const ll INF = 2500000000;

typedef struct {
    ll dist = 0;
    ll node = 0;
    bool gotFlight = false;
} triplet;

struct cmp{
    bool operator()(triplet a, triplet b){
        return a.dist > b.dist;
    }
};

struct Dijkstra{
    vector<vector<P>> roads;
    vector<vector<ll>> flights;
    vector<vector<ll>> dist;
    vector<vector<bool>> visited;
    Dijkstra(ll n){
        roads.resize(n + 1);
        flights.resize(n + 1);
        dist.resize(2, vector<ll>(n + 1, INF));
        visited.resize(2, vector<bool>(n + 1));
    }
    void run(ll start){
        dist[0][start] = 0;
        priority_queue<triplet, vector<triplet>, cmp> pq;
        pq.push({dist[0][start], start, false});

        while (!pq.empty()){
            triplet curr = pq.top();
            pq.pop();

            if(visited[curr.gotFlight][curr.node] ) continue;
            visited[curr.gotFlight][curr.node] = true;

            for(P p: roads[curr.node]){
                ll next_node = p.first, gas = p.second;
                if(dist[curr.gotFlight][next_node] > curr.dist + gas){
                    dist[curr.gotFlight][next_node] = curr.dist + gas;
                    pq.push({dist[curr.gotFlight][next_node], next_node, curr.gotFlight});
                }
            }

            if(!curr.gotFlight && !flights[curr.node].empty()){
                for(ll next_node: flights[curr.node]){
                    if(dist[1][next_node] > curr.dist){
                        dist[1][next_node] = curr.dist;
                        pq.push({dist[1][next_node], next_node, true});
                    }
                }
            }
        }
    }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    // ifstream ifs;
    // ifs.open("secret13.txt");
    
    ll n, m, f, s, t;
    cin >> n >> m >> f >> s >> t;

    Dijkstra graph(n);
    for(ll i = 0; i < m; i++){
        ll from, to, gas;
        cin >> from >> to >> gas;
        graph.roads[from].push_back({to, gas});
        graph.roads[to].push_back({from, gas});
    }

    for(ll i = 0; i < f; i++){
        ll from, to;
        cin >> from >> to;
        graph.flights[from].push_back(to);
    }

    graph.run(s);
    cout << min(graph.dist[0][t], graph.dist[1][t]);
    return 0;
}