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
typedef tuple<int, int, int> tiii;
typedef vector<int> vint;
typedef vector<pii> vpii;
typedef vector<tiii> vtiii;

struct UnionFind {
    vint next;
    UnionFind () { UnionFind(0); }
    UnionFind (int n) { init(n); } 
    void init (int n) { next.resize(n, -1); }
    int find (int curr) {
        if (next[curr] < 0) return curr;
        return next[curr] = find(next[curr]);
    }
    bool merge (int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;

        next[b] = a;
        return true;
    }
};

struct Kruskal {
    #define u_      get<0>
    #define v_      get<1>
    #define weight_ get<2>
    int V, E; // Vertex, Edge number
    vtiii edges;
    UnionFind MST;
    Kruskal () { Kruskal(0, 0); }
    Kruskal (int v, int e) { init(v, e); }
    void init (int v, int e) {
        V = v, E = e;
        MST.init(V);
        edges.resize(E);
    }
    int run () {
        // 1. 간선들을 가중치 순으로 오름차순 정렬하고 정점들을 각 컴포넌트로 초기화
        sort(edges.begin(), edges.end(), [](tiii& t1, tiii& t2){
            return weight_(t1) < weight_(t2); // only compare about weights
        });
    
        // 2. 간선들을 훑으면서 양쪽 정점을 포함한 컴포넌트가 연결되어 있지 않다면 간선을 뽑고 연결한다.
        int res = 0, cnt = 0; // res: 가중치 합, cnt: 뽑은 간선 개수
        for (tiii edge: edges) 
            if (MST.merge(u_(edge), v_(edge))) {
                res += weight_(edge);
                if (++cnt == V-1) break;
            }
        
        // 3. 간선 V-1개가 뽑혔을 때, 그 간선들과 정점들이 이루는 그래프가 MST 이다.
        return res;
    }
};

void solve(int V, int E) {
    Kruskal Tree(V, E);

    int total = 0;
    for (int i = 0; i < E; i++) {
        int x, y, z; cin >> x >> y >> z;
        Tree.edges[i] = tiii(x, y, z);
        total += z;
    }
    cout << total - Tree.run() << endl;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int M, N; // M: 집의 수, N: 길의 수
    while (true) {
        cin >> M >> N;
        if (M == 0 && N == 0) break;
        solve(M, N);
    }
     
    return 0;
}