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
    int N;
    int A[100], B[100];
    vector<int> adj[100];
    bool visited[100];
    MaxMatching(int n) {
        N = n;
        memset(A, -1, sizeof(A));
        memset(B, -1, sizeof(B));
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
            memset(visited, 0, sizeof(visited));
            if (canMatch(a)) match++;
        }

        return match;
    }
    int lastMatchedTime(int lastTime) {
        int time;
        for (time = lastTime - 1; B[time] == -1; time--);
        
        return time + 1;
    }
    void sortAdj() {
        for (int i = 0; i < N; i++)
            sort(adj[i].begin(), adj[i].end());
    }
};

void solve(){
    int N, M; cin >> N >> M;
    int lastTime = 0;
    MaxMatching Graph(N);
    for (int i = 0; i < M; i++) {
        int S, E, pieces;
        cin >> S >> E >> pieces;
        lastTime = max(lastTime, E);

        while (pieces--) {
            int part; cin >> part;
            for (int t = S; t < E; t++)
                Graph.adj[part-1].push_back(t);
        }
    }
    Graph.sortAdj();
    if (N > Graph.run()) cout << -1 << endl;
    else cout << Graph.lastMatchedTime(lastTime) << endl;
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