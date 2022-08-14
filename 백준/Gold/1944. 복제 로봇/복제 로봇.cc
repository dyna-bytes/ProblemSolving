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
        if(v[y].empty()){ std::cout << "  []\n"; continue; } \
        std::cout << "  ["; \
        for(int x = 0; x < ((v[y].size())-1); x++) \
            std::cout << v[y][x] << "|"; \
        std::cout << v[y][(v[y].size())-1] << "]\n"; \
    } \
    std::cout << "]\n"; \
} while(0)
#define endl '\n'
#define Y first
#define X second
typedef long long ll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef vector<int> vint;
typedef vector<pii> vpii;
typedef vector<tiii> vtiii;
const int INF = 1e9;
const int dy[] = {-1, 1, 0, 0}, dx[] = {0, 0, -1, 1};

pii S;
vpii nodes;
int N, M;

vector<vint> grid;

struct UnionFind {
    vint parent;
    UnionFind () { UnionFind(0); }
    UnionFind (int n) { init(n); }
    void init (int n) { parent.resize(n, -1); }

    // find root
    int find (int curr) {
        if (parent[curr] < 0) return curr;
        return parent[curr] = find(parent[curr]);
    }

    // merge b's root to a's root
    bool merge (int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;

        parent[b] = a; // merge b to a
        return true;
    }
};

struct Kruskal {
    #define u__      get<0>
    #define v__      get<1>
    #define weight__ get<2>

    int V, E; // Vertex, Edge number
    vtiii edges;
    UnionFind components;
    Kruskal () { Kruskal(0, 0); }
    Kruskal (int v, int e) { init(v, e); }
    void init (int v, int e) {
        V = v, E = e;
        components.init(V);
        edges.resize(E);
    }
    void addEdge (int u, int v, int w=1){
        edges.push_back({u, v, w});
    }

    int run () {
        sort(edges.begin(), edges.end(), [] (tiii& t1, tiii& t2) {
            return weight__(t1) < weight__(t2); 
        });
    
        int res = 0, cnt = 0; // res: 가중치 합, cnt: 뽑은 간선 개수
        for (tiii edge: edges) 
            if (components.merge(u__(edge), v__(edge))) {
                res += weight__(edge);
                if (++cnt == V-1) break;
            }
        
        return res;
    }
};

int bfs(pii start, pii end) {
    auto inRange = [&](int y, int x){ return y >= 0 && y < N && x >= 0 && x < N; };

    vector<vint> visited(N, vint(N));
    queue<tiii> q;
    q.push({start.Y, start.X, 0});
    visited[start.Y][start.X] = true;
    while (!q.empty()) {
        auto [y, x, d] = q.front(); q.pop();
        if (y == end.Y && x == end.X) return d;

        for (int dir = 0; dir < 4; dir++) {
            int ny = y + dy[dir], nx = x + dx[dir];
            if (!inRange(ny, nx)) continue;
            if (grid[ny][nx] == 1) continue;
            if (visited[ny][nx]) continue;
            visited[ny][nx] = true;
            q.push({ny, nx, d+1});
        }
    }
    return -1;
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> N >> M;
    grid.resize(N, vint(N)); 

    for (int y = 0; y < N; y++) {
        string inp; cin >> inp;
        for (int x = 0; x < N; x++) {
            if (inp[x] == 'S') {
                S = {y, x};
                nodes.push_back({y, x});
            } else if (inp[x] == 'K') {
                nodes.push_back({y, x});
            } else if (inp[x] == '1') {
                grid[y][x] = 1;
            }
        }
    }

    Kruskal MST(N*N, 0);
    for (int i = 0; i < M+1; i++) {
        for (int j = i+1; j < M+1; j++) {
            int w = bfs(nodes[i], nodes[j]);
            if (w == -1) {
                cout << -1;
                return 0;
            }
            MST.addEdge(i, j, w);
        }
    }
    cout << MST.run();

    return 0;
}