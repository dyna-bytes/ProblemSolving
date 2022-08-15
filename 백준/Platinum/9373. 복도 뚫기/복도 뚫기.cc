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
typedef long double ld;
typedef tuple<int, int, ld> tiil;
typedef vector<int> vint;
typedef vector<ld> vld;
typedef vector<tiil> vtiil;

int W, N;

struct UnionFind {
    vint parent;
    void init (int n) { parent.resize(n, -1); }
    int find (int curr) {
        if (parent[curr] < 0) return curr;
        return parent[curr] = find(parent[curr]);
    }
    bool merge (int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        parent[b] = a;
        return true;
    }
};

struct Kruskal {
    #define u__     get<0>
    #define v__     get<1>
    #define weight__ get<2>
    
    int V;
    vtiil edges;
    UnionFind components;
    Kruskal (int n) { init(n); }
    void init (int v) {
        V = v;
        components.init(V);
    }
    void addEdge (ld u, ld v, ld weight) {
        edges.push_back({u, v, weight});
    }
    ld run () {
        sort(edges.begin(), edges.end(), [] (tiil& t1, tiil& t2) {
            return weight__(t1) < weight__(t2);
        });

        int cnt = 0;
        for (tiil edge: edges) {
            if (components.merge(u__(edge), v__(edge))) 
                if (components.find(N) == components.find(N+1)) return weight__(edge);
        }
        return 0;
    }
};


// 벽: y가 t1과 평행한 위치에 있고, x = 0 또는 W, r = 0인 원
ld dist(tiil t1, tiil t2) {
    auto [x1, y1, r1] = t1;
    auto [x2, y2, r2] = t2;

    // case1. 두 원이 접하거나 겹치는 경우
    // case2. 두 원이 떨어져 있는 경우
    ld hyp = hypot(abs(x1-x2), abs(y1-y2)) - (r1 + r2);
    return max(hyp, (ld)0);
}   

void solve () {
    cin >> W >> N;
    if (N == 0) {
        cout << (ld)W/2 << endl;
        return;
    }

    vtiil nodes(N);
    for (int i = 0; i < N; i++) {
        int x, y, r; cin >> x >> y >> r;
        nodes[i] = {x, y, r};
    }
    Kruskal MST(N+2);
    for (int i = 0; i < N; i++) {
        auto [_, parallel_y, __] = nodes[i];
        // N: 왼쪽 벽의 노드 번호, N+1: 오른쪽 벽의 노드 번호
        MST.addEdge(i, N, dist(nodes[i], tiil{0, parallel_y, 0}));
        MST.addEdge(i, N+1, dist(nodes[i], tiil{W, parallel_y, 0}));

        // debug(dist(nodes[i], tiil{0, parallel_y, 0}));
        // debug(dist(nodes[i], tiil{W, parallel_y, 0}));
        for (int j = i+1; j < N; j++) {
            MST.addEdge(i, j, dist(nodes[i], nodes[j]));
            // debug(dist(nodes[i], nodes[j]));
        }
    }
    MST.addEdge(N, N+1, W);

    cout << fixed;
    cout.precision(6);
    cout << MST.run()/(ld)2 << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int T; cin >> T;
    while (T--) solve();
    return 0;
}