#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <math.h>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define endl '\n'
typedef long long ll;
typedef pair<double, double> P;
const double INF = 1000000000;
const int speed = 5;
const int jump_time = 2;
const int jump_dist = 50;

struct Dijkstra{
    int N;
    vector<vector<double>> adj;
    vector<double> time;
    Dijkstra(int n){
        N = n;
        adj.resize(N+2, vector<double>(N+2));
        time.resize(N+2, INF);
    }
    void addAdj(int from, int to, double time){
        adj[from][to] = time;
    }
    void run(int S){
        vector<bool> visited(N+2);
        priority_queue<P, vector<P>, greater<P>> pq;
        time[S] = 0;
        pq.push({time[S], S});
        while(!pq.empty()){
            int curr = pq.top().second; pq.pop();

            if(visited[curr]) continue;
            visited[curr] = true;

            for(int next = 0; next <= N+1; next++){
                double& weight = adj[curr][next];
                if(weight == 0) continue;

                if(time[next] > time[curr] + weight){
                    time[next] = time[curr] + weight;
                    pq.push({time[next], next});
                }
            }
        }
    }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    double sx, sy, ex, ey;
    cin >> sx >> sy >> ex >> ey;

    int n; cin >> n;
    vector<P> pos(n+2);
    pos[0] = {sx, sy}; pos[n+1] = {ex, ey};
    for(int i = 1; i <= n; i++){ // one base
        double x, y; cin >> x >> y;
        pos[i] = {x, y};
    }
    Dijkstra Graph(n);
    for(int here = 1; here <= n; here++){
        for(int there = 1; there <= n; there++){
            if(here == there) continue;

            double x = fabs(pos[here].first - pos[there].first);
            double y = fabs(pos[here].second - pos[there].second);
            double time = hypot(x, y)/speed;
            time = min(time, 2 + fabs(hypot(x, y) - 50)/speed);
  
            Graph.addAdj(here, there, time);
            Graph.addAdj(there, here, time);
        }
    }
    int start = 0, end = n + 1;
    for(int there = 1; there <= end; there++){
        double x = fabs(sx - pos[there].first);
        double y = fabs(sy - pos[there].second);
        double time = hypot(x, y)/speed;

        Graph.addAdj(start, there, time);
    }

    for(int there = 1; there <= n; there++){
        double x = fabs(ex - pos[there].first);
        double y = fabs(ey - pos[there].second);
        double time = hypot(x, y)/speed;
        time = min(time, 2 + fabs(hypot(x, y) - 50)/speed);

        Graph.addAdj(there, end, time);
    }
    Graph.run(0);
    cout << Graph.time[end];
    // for(int i = 0; i <= end; i++)
    //     debug(Graph.time[i]);

    // for(int here = 0; here <= end; here++){
    //     for(int there = 0; there <= end; there++){
    //         cout << Graph.adj[here][there] << " ";
    //     }
    //     cout << endl;
    // }
    return 0;
}