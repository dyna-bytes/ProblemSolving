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

/**
 * @brief Kruskal's algorithm
 * 1. 간선들을 가중치 순으로 오름차순 정렬하고 정점들을 각 컴포넌트로 초기화
 * 2. 간선들을 훑으면서 양쪽 정점을 포함한 컴포넌트가 연결되어 있지 않으면 간선을 뽑고 연결한다.
 * 3. 간선 V-1개가 뽑혔을 때, 그 간선들과 정점들이 이루는 그래프가 MST이다.
 * 
 */


struct UnionFind {
    vector<int> parent;
    UnionFind(int n) { parent.resize(n, -1); }
    // FIND ROOT
    int find(int n) {
        if(parent[n] < 0) return n;
        return parent[n] = find(parent[n]);
    }
    bool merge(int a, int b) {
        a = find(a);
        b = find(b);
        if(a == b) return false;

        parent[b] = a;
        return true;
    }
};

struct Edge {
    int u, v, w;
    Edge(): Edge(-1, -1, 0) {}
    Edge(int u1, int v1, int w1): u(u1), v(v1), w(w1) {}
    bool operator < (const Edge& E) const { return w < E.w; }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N, M; cin >> N >> M;

    UnionFind MST(N);
    vector<Edge> edges(M);

    for (int i = 0; i < M; i++) {
        int u, v, w; cin >> u >> v >> w;
        u--, v--;
        edges[i] = Edge(u, v, w);
    }
    sort(edges.begin(), edges.end());

    // res: 가중치합, cnt: 뽑은 간선 수
    int res = 0, cnt = 0;
    for (Edge edge: edges) {
        if (MST.merge(edge.u, edge.v)) {
            res += edge.w;
            if (++cnt == N-1) break;
        }
    }
    cout << res;

    return 0;
}