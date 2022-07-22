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

const int MAX_X = 100'001;
const int MAX_K = 18; // MAX_K >= log2(MAX_X)

// f(x) satisfies below conditions
// 1. f(x) = f_1(x)
// 2. f_(a+b)(x) = f_b(f_a(x))

struct SparseTable{
    int X;
    int parent[MAX_X][MAX_K] = {0}; // parent[x][k]: f(x)의 2^k번 이동 후인 f_2^k(x)의 값
    int dist[MAX_X][MAX_K] = {0}; // dist[x][k]: x에서 2^k번 이동 후의 깊이
    vector<vector<P>> adj;
    SparseTable(int _X) {
        X = _X;
        adj.resize(X+1);
    }
    void addAdj(int from, int to, int weight=1) { adj[from].push_back({to, weight}); }
    void init(vector<int>& f_1) { // one-based index
        for (int x = 1; x <= X; x++)
            parent[x][0] = f_1[x]; // f_1(x) = parent[x][0];
    }
    // bfs를 통해서 dist[][0], parent[][0] 계산
    void bfs(int start = 1) {
        vector<int> visited(X+1);
        queue<P> q;

        visited[start] = true;
        q.push({start, 0});
        while (!q.empty()) {
            auto [curr, depth] = q.front(); q.pop();

            for (auto [next, weight]: adj[curr]) {
                if (visited[next]) continue;

                parent[next][0] = curr;
                dist[next][0] = weight; // weight = 1이면 시작점으로부터의 깊이
                visited[next] = true;
                q.push({next, weight});
            }
        }
    }
    // 희소 테이블 구축
    void construct() {
        for (int k = 0; k < MAX_K-1; k++)
            for (int x = 1; x <= X; x++) {
                // f_2^(k+1)(x) = f_2^k( f_2^k(x) )
                parent[x][k+1] = parent[ parent[x][k] ][k];
                dist[x][k+1] = dist[x][k] + dist[ parent[x][k] ][k];
            }
    }
    // x에서 N 단계 이동 후의 도착점
    int query(int x, int N) {
        // 켜져 있는 비트에 해당하는 배열만 사용해서 희소테이블을 건너뛴다.
        for (int k = MAX_K-1; k >= 0; k--)
            if (N >= (1 << k)) {
                N -= (1 << k); 
                x = parent[x][k];
            }
        return x;
    }
    // x에서 Weight가 다 닳을 때 까지 이동 후의 도착점
    int query2(int x, int W) {
        for (int k = MAX_K-1; k >= 0; k--)
            if (x == 1) break; // base case
            else if (W >= dist[x][k]) {
                if (parent[x][k]) {
                    W -= dist[x][k];
                    x = parent[x][k];
                }
            }
        return x;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    return 0;
}