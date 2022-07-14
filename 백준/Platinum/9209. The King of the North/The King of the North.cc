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
const int dy[] = {-1, 1, 0, 0}, dx[] = {0, 0, -1, 1};
const int MAX_FLOW = 1e5+1;

struct Edge{
    int to, c, f;
    Edge* dual;
    Edge(int to1, int c1) {
        to = to1, c = c1, f = 0;
        dual = nullptr;
    }
    int residual() { return c - f; }
    void addFlow(int f1) {
        f += f1;
        dual->f -= f1;
    }
};
struct NetworkFlow{
    int N;
    vector<vector<Edge*>> adj;
    NetworkFlow(int n) {
        N = n;
        adj.resize(N+1);
    }
    void addAdj(int from, int to, int cap) {
        Edge* e1 = new Edge(to, cap);
        Edge* e2 = new Edge(from, 0);
        e1->dual = e2;
        e2->dual = e1;
        adj[from].push_back(e1);
        adj[to].push_back(e2);
    }
    ll run(int S, int E) {
        ll total = 0;
        while (true) {
            vector<int> prev(N+1, -1);
            vector<Edge*> path(N+1);
            queue<int> q;
            q.push(S);

            while (!q.empty()) {
                int curr = q.front(); q.pop();
                if (curr == E) break;

                for (auto edge: adj[curr]) {
                    int next = edge->to;
                    if (prev[next] != -1) continue;
                    if (edge->residual() > 0) {
                        prev[next] = curr;
                        path[next] = edge;
                        q.push(next);

                        if (next == E) break;
                    }
                }
            }

            if (prev[E] == -1) break;
            int flow = INF;
            for (int node = E; node != S; node = prev[node])
                flow = min(flow, path[node]->residual());
            for (int node = E; node != S; node = prev[node])
                path[node]->addFlow(flow);
            total += flow;
        }

        return total;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int Y, X; cin >> Y >> X;
    vector<vector<int>> grid(Y, vector<int>(X));
    for (int y = 0; y < Y; y++)
        for (int x = 0; x < X; x++)
            cin >> grid[y][x];

    int sy, sx;
    cin >> sy >> sx;
    int ey = Y, ex = X;

    auto node = [&](int y, int x, int floor = 0) {
        return x + y*X + floor*Y*X;
    };
    auto inRange = [&](int y, int x) {
        return y >= 0 && y < Y && x >= 0 && x < X;
    };
    auto isBoundary = [&](int y, int x) {
        return y == 0 || y == Y-1 || x == 0 || x == X-1;
    };

    NetworkFlow Graph(Y*X*2);
    for (int y = 0; y < Y; y++)
        for (int x = 0; x < X; x++) {
            if (grid[y][x] == 0) continue;
            Graph.addAdj(node(y, x, 0), node(y, x, 1), grid[y][x]);

            if (isBoundary(y, x)) Graph.addAdj(node(y, x, 1), node(ey, ex, 0), INF);
            
            for (int d = 0; d < 4; d++) {
                int ny = y + dy[d], nx = x + dx[d];
                if (!inRange(ny, nx)) continue;
                if (grid[ny][nx] == 0) continue;
                Graph.addAdj(node(y, x, 1), node(ny, nx, 0), INF);
                Graph.addAdj(node(ny, nx, 1), node(y, x, 0), INF);
            }
        }

    cout << Graph.run(node(sy, sx, 0), node(ey, ex, 0));
    
    return 0;
}