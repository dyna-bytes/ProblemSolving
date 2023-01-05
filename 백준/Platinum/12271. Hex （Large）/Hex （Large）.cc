#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define debug(x) cout << "[debug] " << #x << " is " << x << endl
// ↑, ↗, →, ↓, ↙, ←
const int dy[] = {-1, -1, 0, 1, 1, 0}, dx[] = {0, 1, 1, 0, -1, -1};
const int MAX_V = 30000;
const int INF = 1e9;
typedef vector<int> vint;
#define BLUE 1
#define RED 2

struct Edge {
    int to, c, f;
    Edge* dual;
    Edge (int to = -1, int c = 0) {
        this->to = to;
        this->c = c;
        this->f = 0;
        dual = nullptr;
    }
    int residual() {
        return c - f;
    }
    void addFlow(int flow) {
        this->f += flow;
        dual->f -= flow;
    }
};

struct NetworkFlow {
    vector<Edge*> adj[MAX_V];

    void addEdge(int from, int to, int cap = 1) {
        Edge* e1 = new Edge(to, cap);
        Edge* e2 = new Edge(from, 0);
        e1->dual = e2;
        e2->dual = e1;
        adj[from].push_back(e1);
        adj[to].push_back(e2);
    }

    int run(int S, int E) {
        int total = 0;
        int prev[MAX_V];
        Edge* path[MAX_V * 5];

        while (true) {
            memset(path, 0, sizeof(path));
            memset(prev, -1, sizeof(prev));
            queue<int> q;
            q.push(S);
            
            while (!q.empty() && prev[E] == -1) {
                int curr = q.front(); q.pop();
                if (curr == E) break;

                for (Edge* e: adj[curr]) {
                    int next = e->to;

                    if (prev[next] != -1) continue;
                    if (e->residual() <= 0) continue;
                    path[next] = e;
                    prev[next] = curr;
                    q.push(next);

                    if (next == E) break; 
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

int N;
int B, R;
vector<vint> board;
void solve() {
    cin >> N;
    B = R = 0;
    board = {};
    board.resize(N, vint(N));
    for (int y = 0; y < N; ++y)
        for (int x = 0; x < N; ++x) {
            char ch; cin >> ch;
            if (ch == 'B') board[y][x] = BLUE, B++;
            if (ch == 'R') board[y][x] = RED, R++;
        }

    // 0층: 노드에 들어오는 간선, 1층 노드에서 나가는 간선
    auto node = [&](int y, int x, int level) {
        return (y * N + x) + level * N * N;
    };
    auto inRange = [&](int y, int x) {
        return 0 <= y && y < N && 0 <= x && x < N;
    };

    NetworkFlow graph;

    auto setGraph = [&](int color) {
    for (int y = 0; y < N; ++y)
        for (int x = 0; x < N; ++x) {
            if (board[y][x] != color) continue;

            graph.addEdge(node(y, x, 0), node(y, x, 1));
            for (int d = 0; d < 6; ++d) {
                int ny = y + dy[d], nx = x + dx[d];
                if (!inRange(ny, nx)) continue;
                if (board[ny][nx] != color) continue;

                graph.addEdge(node(y, x, 1), node(ny, nx, 0));
                graph.addEdge(node(ny, nx, 1), node(y, x, 0));
            }
        }
    };

    setGraph(BLUE);
    setGraph(RED);

    int source_blue = 2 * N * N;
    int sink_blue = 2 * N * N + 1;
    int source_red = 2 * N * N + 2;
    int sink_red = 2 * N * N + 3;
    for (int y = 0; y < N; ++y) {
        if (board[y][0] == BLUE) graph.addEdge(source_blue, node(y, 0, 0));
        if (board[y][N - 1] == BLUE) graph.addEdge(node(y, N - 1, 1), sink_blue);
    }
    for (int x = 0; x < N; ++x) {
        if (board[0][x] == RED) graph.addEdge(source_red, node(0, x, 0));
        if (board[N - 1][x] == RED) graph.addEdge(node(N - 1, x, 1), sink_red);
    }

    int blue_paths = graph.run(source_blue, sink_blue);
    int red_paths = graph.run(source_red, sink_red);
    
    if (abs(B - R) >= 2 
        || blue_paths >= 2 || (blue_paths && B < R)
        || red_paths >= 2 || (red_paths && R < B)
        ) cout << "Impossible" << endl;
    else if (blue_paths) cout << "Blue wins" << endl;
    else if (red_paths) cout << "Red wins" << endl;
    else cout << "Nobody wins" << endl;
    // debug(blue_paths);
    // debug(red_paths);
}

int main() {
    FASTIO;
    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}