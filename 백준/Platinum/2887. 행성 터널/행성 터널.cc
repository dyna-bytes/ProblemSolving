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
const int INF = 1e9 + 1;

struct UnionFind {
    vint parent;
    UnionFind () { UnionFind(0); }
    UnionFind (int n) { init(n); }
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
    int V, E;
    vtiii edges;
    UnionFind components;
    Kruskal () { Kruskal(0, 0); }
    Kruskal (int v, int e) { init(v, e); }
    void init (int v, int e) {
        V = v, E = e;
        components.init(V);
        edges.resize(E);
    }
    void addEdge (int v, int u, int weight) {
        edges.push_back({v, u, weight});
    }
    int run () {
        sort(edges.begin(), edges.end(), [](tiii& t1, tiii& t2) {
            return get<2>(t1) < get<2>(t2);
        });

        int res = 0, cnt = 0;
        for (const tiii& edge: edges) 
            if (components.merge(get<0>(edge), get<1>(edge))) {
                res += get<2>(edge);
                if (++cnt == V-1) break;
            }
        
        return res;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    auto dist_1D = [](int x1, int x2){ return abs(x1 - x2); };
    
    int N; cin >> N;
    
    vector<vint> planets(N);
    for (int i = 0; i < N; i++) {
        int x, y, z; 
        cin >> x >> y >> z;
        planets[i] = {i, x, y, z};
    }

    Kruskal MST(N, 0);
    // 각 x, y, z축에 대해 정렬
    for (int axis = 1; axis <= 3; axis++){
        sort(planets.begin(), planets.end(), [&](vint& v1, vint& v2) {
            return v1[axis] < v2[axis];
        });

        vint prev = planets[0];
        for (int i = 1; i < N; i++) {
            vint& curr = planets[i];
            MST.addEdge(prev[0], curr[0], dist_1D(prev[axis], curr[axis]));
            prev = curr;
        }
    }

    cout << MST.run();
    return 0;
}