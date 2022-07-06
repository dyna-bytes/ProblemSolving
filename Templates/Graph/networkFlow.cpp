#include <bits/stdc++.h>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define debugVec(v) do { \
    std::cout << "[Debug] ["; \
    for(int i = 0; i < ((v.size())-1); i++) std::cout << v[i] << "|"; \
    std::cout << v[((v.size())-1)] << "]\n"; \
} while(0)
#define debugV2D(v) do { \
    std::cout << "[Debug] [\n"; \
    for(int y = 0; y < (v.size()); y++) { \
        std::cout << "  ["; \
        for(int x = 0; x < ((v[y].size())-1); x++) \
            std::cout << v[y][x] << "|"; \
        std::cout << v[y][(v[y].size())-1] << "]\n"; \
    } \
    std::cout << "]\n"; \
} while(0)
#define endl '\n'
typedef long long ll;
typedef pair<int, int> P;
const int INF = 1e9;

struct Edge{
    int to, c, f; // destination, capacity, flow
    Edge* dual; // points the dual Edge of this one
    Edge(){ 
        Edge(-1, 0); 
    }
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

// Edmonds-Karp algorithm
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
                if(curr == E) break; // if reached end, stop

                for(Edge* e: adj[curr]){ // e: curr-->next
                    int next = e->to;
                    // if visited next, continue
                    if(prev[next] != -1) continue;
                    if(e->residual() > 0){
                        edges[next] = e;
                        prev[next] = curr;
                        q.push(next);

                        if(next == E) break;
                    }
                }
            }

            // if there is no path to reach the end, done.
            if(prev[E] == -1) break;     

            int flow = INF; 
            // get the minimum flow through a path
            for(int node = E; node != S; node = prev[node])
                flow = min(flow, edges[node]->residual());
            // add flow to the path
            for(int node = E; node != S; node = prev[node])
                edges[node]->addFlow(flow);

            total += flow; // add up to the total flow
        }
        return total;
    }

    void debugAdj(){
        cout << endl << "[DebugAdj] : [" << endl;
        for(int curr = 0; curr < adj.size(); curr++){
            cout << "[" << curr << "] -> [";
            for(int next = 0; next < adj[curr].size(); next++){
                cout << next;
                if (next != adj[curr].size()-1) cout << "|";
            }
            cout << "]" << endl;
        }
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    // Usage example
    // problem BOJ 17412: https://www.acmicpc.net/problem/17412

    int N, P; cin >> N >> P;
    NetworkFlow Graph(N);

    for(int i = 0; i < P; i++){
        int from, to; cin >> from >> to;
        Graph.addEdge(from, to, 1); // capa가 1인 단방향 간선 추가
    }

    Graph.debugAdj();
    cout << Graph.run();
    return 0;
}