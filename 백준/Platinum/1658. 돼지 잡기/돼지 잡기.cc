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
                        prev[next] = curr;
                        path[next] = e;
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


int M, N; 
int node(int n, int m){
    return n + N*m;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> M >> N;
    NetworkFlow Graph((N+2)*(M+1)+2);
    int S = 0;
    int E = (N+2)*(M+1)+1;

    vector<int> pigs(M+1);
    for(int i = 1; i <= M; i++){ // one base
        cin >> pigs[i];
    }

    vector<vector<int>> customer(N+1);
    vector<int> buy(N+1);
    for(int n = 1; n <= N; n++){
        int numOfKeys; cin >> numOfKeys;
        for(int k = 0; k < numOfKeys; k++){
            int key; cin >> key;
            customer[n].push_back(key);
        }
        cin >> buy[n];
    }

    for(int n = 1; n <= N; n++){
        for(int m: customer[n]){
            Graph.addAdj(node(n, m), n, INF);
            if(n == N) continue;
            
            for(int m_next: customer[n])
                if(m != m_next) 
                    Graph.addAdj(node(n, m_next), node(n+1, m), INF);
        }
    }

    for(int n = 1; n <= N; n++){
        for(int m = 1; m <= M; m++){
            if(n == 1) Graph.addAdj(S, node(n, m), pigs[m]);
            else       Graph.addAdj(node(n-1, m), node(n, m), INF);
        }
    }

    for(int n = 1; n <= N; n++){
        Graph.addAdj(n, E, buy[n]);
    }

    cout << Graph.run(S, E);
    // for(int i = 0; i <= E; i++){
    //     cout << i << ": ";
    //     for(Edge* e: Graph.adj[i]){
    //         cout << e->to << " ";
    //     }
    //     cout << endl;
    // }
    
    return 0;
}