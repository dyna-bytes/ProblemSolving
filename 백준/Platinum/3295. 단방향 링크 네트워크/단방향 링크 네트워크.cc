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
    vector<int> visited;
    MaxMatching(int n, int m) {
        N = n, M = m;
        A.resize(N+1, -1), B.resize(M+1, -1);
        adj.resize(N+1);
        visited.resize(N+1);
    }
    void addAdj(int from, int to) {
        adj[from].push_back(to);
    }
    bool canMatch(int a) {
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
                fill(visited.begin(), visited.end(), 0);
                if (canMatch(a)) match++;
            }
        }
        return match;
    }
};

/**
 * @brief 이분 매칭이라고 이게..?
 * 
 * 관찰1: 사실 링이든 선형 배열이든 구분할 필요 없이 링크(단방향간선)의 개수만 전부 세면 된다.
 * 관찰2: '링과 선형 배열이 겹치면 안됨' => 모든 노드는 indegree와 outdegree가 2 이상일 수 없다.
 * 
 * 따라서 모든 정점을 나가기만 하는 정점 그룹 A와 들어오기만 하는 그룹 B로 분리한 후,
 * 모든 방향 간선 (u, v)를 u는 A에, v는 B에 포함시켜 나가는 정점에서 들어오는 정점으로 향하는
 * 간선 (u, v)의 최대 간선 개수를 세면 된다.
 * 이 최대 간선 개수는 곧 A에서 B로 흐르는 최대 유량(최대 매칭)과 동치이다.
 * 
 */
void solve(){
    int N, L;
    cin >> N >> L;
    
    MaxMatching Graph(N, N);
    for (int i = 0; i < L; i++) {
        int from, to;
        cin >> from >> to;
        Graph.addAdj(from, to);
    }
    cout << Graph.run() << endl;
};

int main(int argc, char** argv){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int T, test_case;

    cin >> T;
    for(test_case = 0; test_case  < T; test_case++){
        
        // cout << "Case #" << test_case+1 << endl;
        solve();
    }

    return 0;
}