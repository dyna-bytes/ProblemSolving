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
    int residual(){
        return c - f;
    }
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
        adj.resize(N + 1);
    }

    void addEdge(int from, int to, int cap){
        Edge* e1 = new Edge(to, cap);
        Edge* e2 = new Edge(from, 0);
        e1->dual = e2;
        e2->dual = e1;
        adj[from].push_back(e1);
        adj[to].push_back(e2);
    }

    int run(int start = 1, int end = 2){
        int total = 0, S = start, E = end;

        while(true){
            vector<Edge*> edges(N + 1);
            vector<int> prev(N + 1, -1);     
            queue<int> q;
            q.push(S);

            while(!q.empty()){
                int curr = q.front(); q.pop();
                if(curr == E) break;

                for(Edge* e: adj[curr]){
                    int next = e->to;
                    if(prev[next] != -1) continue;
                    if(e->residual() > 0){
                        edges[next] = e;
                        prev[next] = curr;
                        q.push(next);

                        if(next == E) break;
                    }
                }
            }

            if(prev[E] == -1) break;     

            int flow = INT_MAX;
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

    int N, P; cin >> N >> P;
    NetworkFlow Graph(N);

    for(int i = 0; i < P; i++){
        int from, to; cin >> from >> to;
        Graph.addEdge(from, to, 1);
    }

    cout << Graph.run();
    
    return 0;
}