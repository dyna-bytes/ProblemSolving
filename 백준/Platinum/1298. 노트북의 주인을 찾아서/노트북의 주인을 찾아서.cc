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

struct MaxMatching{
    int N, M;
    vector<int> A, B;
    vector<vector<int>> adj;
    vector<bool> visited;
    MaxMatching(int n, int m) {
        N = n, M = m;
        A.resize(100+1, -1), B.resize(100+1, -1);
        adj.resize(100+1);
        visited.resize(100+1);
    }
    bool canMatch(int a){
        if (visited[a]) return false;
        visited[a] = true;
        for (int b: adj[a]) {
            if (B[b] == -1 || canMatch(B[b])) {
                A[a] = b;
                B[b] = a;
                return true;
            }
        }
        return false;
    }
    int run() {
        int match = 0;
        for (int a = 0; a < N; a++) {
            if (A[a] == -1) {
                visited = vector<bool> (100+1, false);
                if (canMatch(a)) match++;
            }
        }
        return match;
    }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N, M; cin >> N >> M;
    MaxMatching Graph(N, M);
    for (int i = 0; i < M; i++) {
        int u, v; cin >> u >> v;
        Graph.adj[u-1].push_back(v-1);
    }
    cout << Graph.run();
    return 0;
}