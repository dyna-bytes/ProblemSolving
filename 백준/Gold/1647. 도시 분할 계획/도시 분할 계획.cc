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
typedef long long ll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef vector<int> vint;
typedef vector<pii> vpii;
typedef vector<tiii> vtiii;

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
                if (++cnt == V-2) break;
            }
        
        return res;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int N, M; 
    cin >> N >> M;
    Kruskal MST(N, M);
    for (int i = 0; i < M; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        MST.addEdge(a-1, b-1, c);
    }
    cout << MST.run();
    return 0;
}