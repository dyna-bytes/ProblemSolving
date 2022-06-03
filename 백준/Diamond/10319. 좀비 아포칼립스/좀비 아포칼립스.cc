#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define endl '\n'
typedef long long ll;
const int INF = 1000000000;

struct Edge{
    int to, c, f;
    Edge* dual;
    Edge(int to1, int c1){
        to = to1, c = c1, f = 0;
        dual = nullptr;
    }
    int residual(){ return c - f; }
    void addFlow(int f1){
        f += f1;
        dual-> f -= f1;
    }
};
struct NetworkFlow{
    int N;
    vector<vector<Edge*>> adj;
    NetworkFlow(int n){
        N = n;
        adj.resize(N+1);
    }
    void addAdj(int from, int to, int cap){
        Edge* e1 = new Edge(to, cap);
        Edge* e2 = new Edge(from, 0);
        e1->dual = e2;
        e2->dual = e1;
        adj[from].push_back(e1);
        adj[to].push_back(e2);
    }
    int run(int S, int E){
        int total = 0;
        
        while(true){
            vector<int> prev(N+1, -1);
            vector<Edge*> path(N+1);

            queue<int> q;
            q.push(S);
            while(!q.empty()){
                int curr = q.front(); q.pop();
                if(curr == E) break;

                for(Edge* e: adj[curr]){
                    int next = e->to;
                    if(prev[next] != -1) continue;
                    if(e->residual() > 0){
                        path[next] = e;
                        prev[next] = curr;
                        q.push(next);
                        if(next == E) break;
                    }
                }
            }
            if(prev[E] == -1) break;

            int flow = INF;
            for(int node = E; node != S; node = prev[node])
                flow = min(flow, path[node]->residual());
            for(int node = E; node != S; node = prev[node])
                path[node]->addFlow(flow);

            total += flow;
        }
        return total;
    }
};  
int node(int n, int timelimit, int t){
    return n * (timelimit + 1) + t;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int T; cin >> T;
    while(T--) {
        int N; cin >> N;
        int start, people, timelimit; cin >> start >> people >> timelimit;
        
        NetworkFlow Graph((N + 1)*(timelimit + 1) + 2);
        int M; cin >> M;
        vector<int> hospital(M);
        for(int i = 0; i < M; i++){
            cin >> hospital[i];
        }
        int R; cin >> R;
        for(int i = 0; i < R; i++){
            int from, to, p, t; cin >> from >> to >> p >> t;
            for(int i = t; i <= timelimit; i++){
                Graph.addAdj(node(from, timelimit, i - t), node(to, timelimit, i), p); 
            }
        }

        // add edge from source to start
        int S = node(N+1, timelimit, 0);
        Graph.addAdj(S, node(start, timelimit, 0), people);
        
        // add edge from hospitals to sink
        int E = node(N+1, timelimit, 1);
        for(int h: hospital)
            Graph.addAdj(node(h, timelimit, timelimit), E, INF);

        // add edge self-connecting to the node itself
        for(int here = 1; here <= N; here++)
            for(int time = 0; time < timelimit; time++)
                Graph.addAdj(node(here, timelimit, time), node(here, timelimit, time + 1), INF);

        cout << Graph.run(S, E) << endl;
    }
    return 0;
}