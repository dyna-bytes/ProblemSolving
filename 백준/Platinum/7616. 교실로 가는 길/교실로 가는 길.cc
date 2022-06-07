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
        dual->f -= f1;
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
            // for(int node = E; node != S; node = prev[node])
            //     cout << node << "->";
            // cout << S << endl;

            total += flow;
        }
        return total;
    }
    
    void print(int S, int E){
        cout << 1 << " ";
        for(int curr = S; curr != E; ){
            if(curr < N/2) cout << curr << " ";

            for(Edge* e: adj[curr]){
                int next = e->to;
                if(e->f == 1){
                    e->f = 0;
                    curr = next;
                    break;
                }
            }
        }
        cout << 2 << endl;
    }
};
int main(){
    int cnt = 1;
    while(true){        
        int K, N; scanf("%d%d", &K, &N);
        if(K == 0 && N == 0) break; 
        NetworkFlow Graph(2*(N+1));

        for(int from = 1; from <= N; from++){
            while(true){
                int to;
                char x;
                scanf("%d%c", &to, &x);

                int from2 = from + N;
                int to2 = to + N;
                Graph.addAdj(from2, to, 1);
                // Graph.addAdj(to2, from, 1);
                
                if(x == '\n') break;
            }
        }

        // for(int node = 1; node <= N; node++){
        //     cout << node << " : ";
        //     for(Edge* e : Graph.adj[node]){
        //         cout << e->to << " ";
        //     }
        //     cout << endl;
        // }
        for(int node = 1; node <= N; node++){
            int node2 = node + N;
            Graph.addAdj(node, node2, 1);
        }

        int ret = Graph.run(1+N, 2);
        // debug(ret);

        cout << "Case " << cnt++ << ":" << endl;
        if(ret >= K){
            for(int i = 0; i < K; i++)
                Graph.print(1+N, 2);
            cout << endl;
        }
        else{
            cout << "Impossible" << endl;
            cout << endl;
        }
    }
    
    return 0;
}