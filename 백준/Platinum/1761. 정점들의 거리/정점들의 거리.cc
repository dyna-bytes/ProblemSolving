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
typedef pair<int, int> pii;
typedef vector<int> vint;
typedef vector<pii> vpii;

const int MAX = 40001;
const int MAX_K = 16;

vector<vint> parent(MAX, vint(MAX_K, -1));
vector<vpii> adj(MAX);
vint depth(MAX, -1); // 루트부터의 깊이
vint dist(MAX); // 루트부터의 거리

struct LCA {
    int N;
    LCA (int n) { N = n; }
    void makeTree(int curr) {
        for (auto [next, weight]: adj[curr]) {
            if (depth[next] == -1) {
                parent[next][0] = curr;
                depth[next] = depth[curr] + 1;
                dist[next] = dist[curr] + weight;
                makeTree(next);
            }
        }
    }
    void construct() {
        for (int k = 0; k < MAX_K-1; k++) 
            for (int x = 0; x < N; x++)
                if (parent[x][k] != -1)
                    parent[x][k+1] = parent[ parent[x][k] ][k];
    }
    int getLCA(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        int diff = depth[u] - depth[v];

        for (int k = MAX_K-1; k >= 0; k--)
            if (diff >= (1 << k)) {
                diff -= (1 << k);
                u = parent[u][k];
            }

        if (u != v) {
            for (int k = MAX_K-1; k >= 0; k--) {
                if (parent[u][k] != -1 && parent[u][k] != parent[v][k]) {
                    u = parent[u][k];
                    v = parent[v][k];
                }
            }
            u = parent[u][0];
        }
        return u;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N; cin >> N;
    LCA Tree(N);

    int root = -1;
    for (int i = 0; i < N-1; i++) {
        int u, v, dist;
        cin >> u >> v >> dist;
        u--, v--;
        
        adj[u].push_back({v, dist});
        adj[v].push_back({u, dist});
        if (root == -1) root = u;
    }
    
    depth[root] = 0;
    dist[root] = 0;
    Tree.makeTree(root);
    Tree.construct();

    int Q; cin >> Q;
    for (int i = 0; i < Q; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        int w = Tree.getLCA(u, v);
        
        int u2w = (dist[u] - dist[root]) - (dist[w] - dist[root]);
        int v2w = (dist[v] - dist[root]) - (dist[w] - dist[root]);
        cout << u2w + v2w << endl;
    }
    return 0;
}