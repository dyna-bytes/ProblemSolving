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

const int MAX = 100'001;
const int MAX_K = 17;

vector<vint> parent(MAX, vint(MAX_K, -1));
vector<vint> adj(MAX);
vint depth(MAX, -1);

struct LCA {
    int N;
    LCA (int n, int root) { N = n; depth[root] = 0; }
    void makeTree (int curr) {
        for (int next: adj[curr]) {
            if (depth[next] != -1) continue;

            parent[next][0] = curr;
            depth[next] = depth[curr] + 1;
            makeTree(next);
        }
    }
    void construct () {
        for (int k = 0; k < MAX_K-1; k++) 
            for (int x = 0; x < N; x++)
                if (parent[x][k] != -1)
                    parent[x][k+1] = parent[ parent[x][k] ][k];
    }
    int getLCA (int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        int diff = depth[u] - depth[v];
        
        for (int k = MAX_K-1; k >= 0; k--)
            if (diff & (1 << k))
                u = parent[u][k];
        
        if (u == v) return u;

        for (int k = MAX_K-1; k >= 0; k--) 
            if (parent[u][k] != -1 && parent[u][k] != parent[v][k]) {
                u = parent[u][k];
                v = parent[v][k];
            }
        u = parent[u][0];

        return u;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N; cin >> N;
    for (int i = 0; i < N-1; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int real_root = 0;
    LCA Tree(N, real_root);
    Tree.makeTree(real_root);
    Tree.construct();

    int Q; cin >> Q;
    for (int i = 0; i < Q; i++) {
        int r, u, v; cin >> r >> u >> v;
        r--, u--, v--;

        // r과 u, u와 v, r과 v의 LCA 중 가장 깊이가 깊은 노드가
        // r을 루트로 삼을 때의 u와 v의 LCA이다.
        int r_u = Tree.getLCA(r, u);
        int r_v = Tree.getLCA(r, v);
        int u_v = Tree.getLCA(u, v);

        int res;
        res = depth[r_u] >= depth[r_v] ? r_u : r_v;
        res = depth[res] >= depth[u_v] ? res : u_v;
        cout << res + 1 << endl;
    }
    return 0;
}