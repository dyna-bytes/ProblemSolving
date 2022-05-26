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
    Edge(){
        Edge(-1, 0);
    }
    Edge(int to1, int c1){
        to = to1;
        c = c1;
        f = 0;
        dual = nullptr;
    }
    int residual(){
        return c - f;
    }
    void addFlow(int f1){
        f += f1;
        dual->f -= f1;
    }
};

struct NetworkFlow{
    int N, M, SIZE;
    vector<vector<Edge*>> adj;

    NetworkFlow(int n, int m){
        N = n; M = m;
        SIZE = n + m + 2;
        adj.resize(SIZE);
    }

    void debugAdj(){
        for(int node = 0; node < SIZE; node++){
            for(int next = 0; next < adj[node].size(); next++){
                cout << "(" << node << ", " << adj[node][next]->to << ") ";
            }
            cout << endl;
        }
    }

    void addEdge(int from, int to, int cap){
        Edge* e1 = new Edge(to, cap);
        Edge* e2 = new Edge(from, 0);
        e1->dual = e2;
        e2->dual = e1;
        adj[from].push_back(e1);
        adj[to].push_back(e2);
    }

    int run(){
        int total = 0, S = 0, E = N + M + 1;

        while(true){
            vector<int> prev(SIZE, -1);
            vector<Edge*> edges(SIZE);

            queue<int> q;
            q.push(S);
            while(!q.empty()){
                int curr = q.front(); q.pop();
                // debug(curr);
                // if visited the end, stop 
                if(prev[E] != -1) break;

                for(Edge* e: adj[curr]){
                    int next = e->to;
                    // debug(next);
                    // if visited next, continue
                    if(prev[next] != -1) continue;
                    if(e->residual() > 0){
                        edges[next] = e;
                        prev[next] = curr;
                        // debug(e->to);
                        q.push(next);

                        if(next == E) break;
                    }
                }
            }

            // if there is no path to reach the end, done.
            if(prev[E] == -1) break;

            int flow = INF;
            for(int node = E; node != S; node = prev[node])
                flow = min(flow, edges[node]->residual());
            
            for(int node = E; node != S; node = prev[node])
                edges[node]->addFlow(flow);
            
            total += flow;
        }
        return total;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int N, M;
    cin >> N >> M;
    NetworkFlow Graph(N, M);
    int S = 0, E = N + M + 1;
    for(int to = 1; to <= N; to++){
        Graph.addEdge(S, to, 1);
        Graph.addEdge(to, S, 0);
    }
    
    for(int from = N + 1; from <= N + M; from++){
        Graph.addEdge(from, E, 1);
        Graph.addEdge(E, from, 0);
    }

    for(int from = 1; from <= N; from++){
        int cnt; cin >> cnt;
        while(cnt--){
            int to; cin >> to;
            to += N;
            Graph.addEdge(from, to, 10);
            Graph.addEdge(to, from, 0);
        }   
    }
    // Graph.debugAdj();
    cout << Graph.run();
    return 0;
}