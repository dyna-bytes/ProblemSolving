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
    void addEdge(int from, int to, int cap){
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

            // BFS
            queue<int> q;
            q.push(S);
            while(!q.empty()){
                int curr = q.front(); q.pop();
                if(curr == E) break;

                for(Edge* curr2next: adj[curr]){
                    int next = curr2next->to;
                    if(prev[next] != -1) continue;
                    if(curr2next->residual() > 0){
                        prev[next] = curr;
                        path[next] = curr2next;
                        q.push(next);
                        
                        if(next == E) break;
                    }
                }
            }
            if(prev[E] == -1) break;

            int flow = INT_MAX;
            for(int node = E; node != S; node = prev[node])
                flow = min(flow, path[node]->residual());
            for(int node = E; node != S; node = prev[node])
                path[node]->addFlow(flow);

            // cout << "show the path" << endl;
            // for(int node = E; node != S; node = prev[node])
            //     cout << node << "->";
            // cout << "S" << endl;

            // debug(flow);
            total += flow;
        }
        return total;
    }
    // E로 들어가는 모든 간선이 포화인가?
    bool check(int E){
        for(Edge* e: adj[E]){
            if(e->dual->residual() > 0){ 
                return false;
            }
        }
        return true;
    }

};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int T; cin >> T;
    while(T--){
        int N; cin >> N;
        vector<int> army(N+1);
        vector<vector<int>> ADJ(N+1, vector<int> (N+1));

        for(int i = 1; i <= N; i++) // one base
            cin >> army[i];

        for(int here = 0; here < N; here++){
            string val; cin >> val;
            for(int there = 0; there < N; there++)
                if(val[there] == 'Y')
                    ADJ[here+1][there+1] = ADJ[there+1][here+1] = true; // one base
        }

        int S = 0, E = 2*N+1;
        // int k = 4;
        // NetworkFlow Graph(2*N+2); // S = 0, T = 2N+1
        // for(int node = 1; node <= N; node++)
        // Graph.addEdge(S, node, army[node]);

        // for(int node = 1; node <= N; node++){
        //     if(army[node] == 0) continue;
        //     bool enemyConnected = false;            
        //     for(int next = 1; next <= N; next++){
                
        //         if(ADJ[node][next] || node == next) {
        //             if(army[next] == 0){ // 적진 노드와 이웃해 있다면 node'->E: cap = k로 설정
        //                 enemyConnected = true;
        //             }else{
        //                 Graph.addEdge(node, next + N, INT_MAX);
        //             }
        //         }
        //     }
        //     if(enemyConnected){
        //         Graph.addEdge(node + N, E, k);
        //     }else{
        //         Graph.addEdge(node + N, E, 1); // 적진 노드와 이웃해있지 않다면 node'->E: cap = 1로 설정
        //     }
        // }
        // debug(Graph.run(S, E));
        // debug(Graph.check(E));


        int lo = 0, hi = 100000;
        while(lo + 1 < hi){
            int mid = (lo + hi)/2;
            
            NetworkFlow Graph(2*N+2); // S = 0, T = 2N+1
            for(int node = 1; node <= N; node++)
            Graph.addEdge(S, node, army[node]);

            for(int node = 1; node <= N; node++){
                if(army[node] == 0) continue;
                bool enemyConnected = false;            
                for(int next = 1; next <= N; next++){
                    
                    if(ADJ[node][next] || node == next) {
                        if(army[next] == 0){ // 적진 노드와 이웃해 있다면 node'->E: cap = k로 설정
                            enemyConnected = true;
                        }else{
                            Graph.addEdge(node, next + N, INT_MAX);
                        }
                    }
                }
                if(enemyConnected){
                    Graph.addEdge(node + N, E, mid);
                }else{
                    Graph.addEdge(node + N, E, 1); // 적진 노드와 이웃해있지 않다면 node'->E: cap = 1로 설정
                }
            }

            Graph.run(S, E);
            if(Graph.check(E)) lo = mid;
            else hi = mid;
        }
        cout << lo << endl;
        
    }
    return 0;
}