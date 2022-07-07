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
        adj.resize(N+1);
        visited.resize(N+1);
    }
    bool canMatch(int a){
        visited[a] = true;
        for (int b: adj[a]) {
            if (B[b] == -1 || !visited[B[b]] && canMatch(B[b])) {
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
            if (A[a] == -1){
                visited.clear(), visited.resize(N+1);
                if (canMatch(a)) match++;
            }
        }
        return match;
    }
};

void solve(){
    int books, students;
    cin >> books >> students;
    MaxMatching Graph(students, books);
    // 학생 그룹을 A로, 책 그룹을 B로 하자
    for(int i = 0; i < students; i++){
        int a, b; cin >> a >> b;
        for(int j = a-1; j <= b-1; j++)
            Graph.adj[i].push_back(j);
    }

    cout << Graph.run() << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int T; cin >> T;
    while(T--){
        solve();
    }
    
    return 0;
}