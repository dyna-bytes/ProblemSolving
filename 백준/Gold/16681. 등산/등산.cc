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

const ll INF = 2e14;
ll healthPerDist;
ll achievePerHeight;

struct Dijkstra{
    ll N;
    vector<vector<P>> adj;
    vector<ll> height;
    vector<ll> distFromStart, distToEnd;
    Dijkstra(ll n){
        N = n;
        adj.resize(N+1);
        distFromStart.resize(N+1, INF);
        distToEnd.resize(N+1, INF);
        height.resize(N+1);
    }

    void setAdj(ll from, ll to, ll dist){
        adj[from].push_back({to, dist});
    }

    void run(ll S, vector<ll>& dist){
        vector<bool> visited;
        visited.resize(N+1);

        dist[S] = 0;
        priority_queue<P, vector<P>, greater<P>> pq;
        pq.push({dist[S], S});

        while(!pq.empty()){
            ll curr = pq.top().second; pq.pop();
            if(visited[curr]) continue;
            visited[curr] = true;
            
            for(P p: adj[curr]){
                ll next = p.first, weight = p.second;
                if(height[next] <= height[curr]) continue;
                if(dist[next] > dist[curr] + weight){
                    dist[next] = dist[curr] + weight;
                    
                    pq.push({dist[next], next});
                }
            }
        }
    }

    void debugArray(){
        for(ll i = 1; i <= N; i++)
            cout << "(" << i << ", " << distFromStart[i] << ") ";
    }

    ll calculateMaxValue(){
        bool IMPOSSIBLE = true;
        for(ll i = 1; i <= N; i++){
            if(distFromStart[i] != INF && distToEnd[i] != INF) IMPOSSIBLE = false;

            distFromStart[i] += distToEnd[i];
            distFromStart[i] *= healthPerDist;        
        }

        for(ll i = 1; i <= N; i++){
            height[i] *= achievePerHeight;
            height[i] -= distFromStart[i];
        }

        if(IMPOSSIBLE) return -INF;
        return *max_element(&height[1], &height[N]);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    ll N, M; cin >> N >> M >> healthPerDist >> achievePerHeight;

    Dijkstra Graph(N);
    for(ll i = 1; i <= N; i++){
        cin >> Graph.height[i];
    }
    for(ll i = 0; i < M; i++){
        ll from, to, dist;
        cin >> from >> to >> dist;
        Graph.setAdj(from, to, dist);
        Graph.setAdj(to, from, dist);
    }
    Graph.run(1, Graph.distFromStart);
    Graph.run(N, Graph.distToEnd);
    ll ret = Graph.calculateMaxValue();

    if(ret == -INF) cout << "Impossible";
    else cout << ret;
    return 0;
}