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
    MaxMatching(int n, int m){
        N = n, M = m;
        A.resize(N+1, -1), B.resize(M+1, -1);
        adj.resize(N+1);
        visited.resize(N+1);
    }
    bool canMatch(int a){
        if (visited[a]) return false;
        visited[a] = true;
        for(int b: adj[a]){
            if (B[b] == -1 || canMatch(B[b])) {
                A[a] = b;
                B[b] = a;
                return true;
            }
        }
        return false;
    }
    int run(){
        int match = 0;
        for(int a = 0; a < N; a++){
            if (A[a] == -1) {
                fill(visited.begin(), visited.end(), 0);
                if (canMatch(a)) match++;
            }
        }
        return match;
    }
    void debugAdj(){
        cout << endl;
        for (int n = 0; n < adj.size(); n++) {
            cout << n << "->|";
            for (int m = 0; m < adj[n].size(); m++)
                cout << adj[n][m] << "|";
            cout << endl;
        }
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N, M;
    cin >> N >> M;
    MaxMatching Graph(N*2, M);
    for(int i = 0; i < N; i++){
        int cnt; cin >> cnt;
        while(cnt--){
            int job; cin >> job;
            job--;
            Graph.adj[i*2].push_back(job);
            Graph.adj[i*2+1].push_back(job);
        }
    }
    cout << Graph.run();
    // Graph.debugAdj();

    return 0;
}