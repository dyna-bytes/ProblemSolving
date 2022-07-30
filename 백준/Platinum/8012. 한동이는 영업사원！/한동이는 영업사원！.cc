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

const int MAX = 30'001;
const int MAX_K = 15;

vector<vint> parent(MAX, vint(MAX_K, -1));
vector<vint> adj(MAX);
vint depth(MAX, -1); // 루트로부터의 깊이

struct LCA {
    int N;
    LCA (int n) { N = n; }
    void makeTree(int curr) {
        for (int next: adj[curr]) 
            if (depth[next] == -1) {
                parent[next][0] = curr;
                depth[next] = depth[curr] + 1;
                makeTree(next);
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
            if (diff & (1 << k)) 
                u = parent[u][k];

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

    for (int i = 0; i < N-1; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    depth[0] = 0; // start from 0. (Think as Zero-based index)
    Tree.makeTree(0);
    Tree.construct();

    int start = 0;
    int sum = 0;

    int Q; cin >> Q;
    for (int i = 0; i < Q; i++) {
        int end; cin >> end;
        end--;

        int lca = Tree.getLCA(start, end);
        int start2lca = depth[start] - depth[lca];
        int end2lca = depth[end] - depth[lca];
        sum += (start2lca + end2lca);

        start = end;
    }   
    cout << sum;
    return 0;
}