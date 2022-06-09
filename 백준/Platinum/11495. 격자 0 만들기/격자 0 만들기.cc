#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define endl '\n'
typedef long long ll;
const int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, -1, 1};
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

int Y, X; 
int node(int y, int x){
    return x + y * X;
}
bool inRange(int y, int x){
    return y >= 0 && y < Y && x >= 0 && x < X;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int T; cin >> T;
    while(T--){
        cin >> Y >> X;
        NetworkFlow Graph(Y*X+2);
        int S = Y*X, E = Y*X + 1;

        vector<vector<int>> grid(Y, vector<int>(X));

        int sum = 0;
        for(int y = 0; y < Y; y++)
            for(int x = 0; x < X; x++){
                cin >> grid[y][x];
                sum += grid[y][x];
            }

        for(int y = 0; y < Y; y++){
            for(int x = 0; x < X; x++){
                if((y+x) % 2 == 0){
                    Graph.addAdj(S, node(y, x), grid[y][x]);
                    for(int d = 0; d < 4; d++){
                        int ny = y + dy[d], nx = x + dx[d];
                        if(!inRange(ny, nx)) continue;
                        Graph.addAdj(node(y, x), node(ny, nx), INF);
                    }
                }
                else{
                    Graph.addAdj(node(y, x), E, grid[y][x]);
                }
            }
        }

        int flow = Graph.run(S, E);
        cout << sum - flow << endl;
    }
    
    return 0;
}