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
typedef vector<int> vint;

const int MAX = 100001;
const int MAX_K = 18;

vector<vint> parent(MAX, vint(MAX_K, -1));
vint depth(MAX, -1);
vector<vint> adj(MAX);

struct LCA{
    int N;
    LCA(int n) {
        N = n;
    }
    // dfs 돌며 parent[i][0], depth[i] 채움
    void makeTree(int curr) {
        for (int next: adj[curr]) 
            if (depth[next] == -1) {
                parent[next][0] = curr;
                depth[next] = depth[curr] + 1;
                makeTree(next);
            }
    }
    void construct() {
        for (int k = 0; k < MAX_K - 1; k++) 
            for (int x = 1; x < N; x++) 
                if (parent[x][k] != -1)
                    parent[x][k+1] = parent[ parent[x][k] ][k];
    }
    int query(int u, int v) {
        // keep depth[u] >= depth[v]
        if (depth[u] < depth[v]) swap(u, v);
        int diff = depth[u] - depth[v];

        // 깊이 차(diff)를 없애며 u를 위로 이동시킴
        for (int k = MAX_K-1; k >= 0; k--) {
            if (diff >= (1 << k)) {
                diff -= (1 << k);
                u = parent[u][k];
            }
        }

        // u와 v가 다르면 동시에 일정 높이만큼 위로 이동시킴
        if (u != v) {
            for (int k = MAX_K-1; k >= 0; k--) {
                if (parent[u][k] != -1 && parent[u][k] != parent[v][k]) {
                    u = parent[u][k];
                    v = parent[v][k];
                }
            }
            // 마지막에 두 정점 u, v의 "부모"가 같으므로 한 번 더 올림
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

    depth[0] = 0;
    Tree.makeTree(0); // 0번 노드를 루트노드로 지정
    Tree.construct();

    int Q; cin >> Q;
    for (int i = 0; i < Q; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        cout << Tree.query(u, v) + 1 << endl;
    }
    
    return 0;
}