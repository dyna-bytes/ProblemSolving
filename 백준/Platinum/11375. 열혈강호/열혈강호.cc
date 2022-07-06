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

    MaxMatching(int n, int m){
        N = n, M = m;
        A.resize(N+1, -1), B.resize(M+1, -1);
        adj.resize(N+1); // 그룹 A에 속한 정점 a들의 인접 리스트
        visited.resize(N+1); // 그룹 A 관점에서의 방문배열
    }
    // A 그룹에 속한 정점 a를 이분 매칭시켜서 성공하면 true
    bool dfs(int a){
        visited[a] = true;
        for (int b: adj[a]) {
            // B[b]: B그룹의 정점 b에 기존에 매칭된 정점 prev_a
            if (B[b] == -1 || !visited[B[b]] && dfs(B[b])) {
                // 반대편이 매칭되지 않았거나
                // 매칭되어 있었지만 원래 매칭되어 있던 정점 prev_a를 다른 정점과 매칭시킬 수 있다면 성공
                A[a] = b;
                B[b] = a;
                return true;
            }
        }
        return false;
    }
    int run(){
        int match = 0;
        for (int a = 0; a < N; a++) {
            // 아직 매칭되지 않은 그룹 A의 정점 a에 대해 매칭 시도
            if (A[a] == -1) {
                // 매 dfs마다 visit배열 초기화
                visited.clear(); visited.resize(N+1);
                if (dfs(a)) match++;
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

    for (int n = 0; n < N; n++) {
        int cnt; cin >> cnt;
        while (cnt--) {
            int m; cin >> m;
            Graph.adj[n].push_back(m-1);
        }
    }

    cout << Graph.run();

    return 0;
}