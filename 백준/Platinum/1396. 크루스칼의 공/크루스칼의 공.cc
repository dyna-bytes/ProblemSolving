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

const int MAX = 200000;
const int MAX_K = 19;

struct Edge {
    int u, v, w;
    Edge(): Edge(-1, -1, 0) {}
    Edge(int u1, int v1, int w1): u(u1), v(v1), w(w1) {}
    bool operator < (const Edge& E) const { return w < E.w; }
};

struct Node {
    bool isLeaf;
    int cost, size;
    Node(): isLeaf(true), cost(0), size(1) {}
    Node(int c1, int s1): isLeaf(false), cost(c1), size(s1) {}
};

vector<Node> generated_tree(MAX);
vector<vint> parent(MAX, vint(MAX_K, -1));
vector<vint> adj(MAX);
vint depth(MAX, -1); // 루트로부터의 깊이
vint next_(MAX, -1); // 유니온파인드에서의 부모 노드

struct LCA {
    int N;
    LCA (int n) { N = n; }
    void makeTree(int curr) {
        for (int next: adj[curr]) {
                // if (next == curr) continue;
                // parent[next][0] = curr;
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

struct UnionFind {
    // FIND ROOT
    int find(int n) {
        if (next_[n] < 0) return n;
        return next_[n] = find(next_[n]);
    }
    bool merge(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;

        next_[b] = a;
        return true;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int N, M; cin >> N >> M; // N:정점의 개수, M:간선의 개수

    UnionFind disjoint_set;
    vector<Edge> edges(M);
    for (int i = 0; i < M; i++) {
        int a, b, w; cin >> a >> b >> w;
        a--, b--;
        edges[i] = Edge(a, b, w);
    }
    sort(edges.begin(), edges.end());

    int curr = N;
    for (Edge edge: edges) {
        int uRoot = disjoint_set.find(edge.u);
        int vRoot = disjoint_set.find(edge.v);
        if (uRoot == vRoot) continue;

        curr++;
        generated_tree[curr] = Node(edge.w, 
            generated_tree[uRoot].size + generated_tree[vRoot].size);
        
        adj[curr].push_back(uRoot);
        adj[curr].push_back(vRoot);
        parent[uRoot][0] = curr;
        parent[vRoot][0] = curr;
        disjoint_set.merge(curr, uRoot);
        disjoint_set.merge(curr, vRoot);
    }

    // for (int i = N+1; i <= curr; i++) {
    //     Node node = generated_tree[i];
    //     cout << "[" << i << "] {cost: " << node.cost << ", size: " << node.size << "}" << endl; 
    // }

    LCA Tree(curr+1);
    // for every components in forest, build LCA sparse tables
    // 누가 트리의 루트인지 알 수 없으니까, 그냥 부모자식 관계 있는 서브트리마다 다 dfs 돌려봄
    for (int i = 0; i <= curr; i++) 
        if (parent[i][0] == -1) {
            depth[i] = 0;
            Tree.makeTree(i);
        }
    Tree.construct();

    int Q; cin >> Q;
    for (int i = 0; i < Q; i++) {
        int x, y; cin >> x >> y;
        x--, y--;

        if (disjoint_set.find(x) != disjoint_set.find(y)) {
            cout << -1 << endl;
            continue;
        }

        int lca = Tree.getLCA(x, y);
        cout << generated_tree[lca].cost << " " << generated_tree[lca].size << endl;
    }
    
    return 0;
}