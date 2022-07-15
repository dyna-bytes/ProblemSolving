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
    void addAdj(int from, int to) { adj[from].push_back(to); }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N; cin >> N;
    vector<vector<char>> board(N, vector<char>(N));
    for (int y = 0; y < N; y++)
        for (int x = 0; x < N; x++)
            cin >> board[y][x];
    
    vector<vector<int>> hmap(N, vector<int>(N));
    vector<vector<int>> vmap(N, vector<int>(N));
    int num = 0;
    for (int y = 0; y < N; y++) {
        bool isFirstPawn = false;
        num++;
        for (int x = 0; x < N; x++) {
            if (board[y][x] == '.') {
                hmap[y][x] = num;
                isFirstPawn = true;
            } else if (board[y][x] == 'X' && isFirstPawn) {
                num++;
                isFirstPawn = false;
            }
        }
    }

    for (int x = 0; x < N; x++) {
        bool isFirstPawn = false;
        num++;
        for (int y = 0; y < N; y++) {
            if (board[y][x] == '.') {
                vmap[y][x] = num;
                isFirstPawn = true;
            } else if (board[y][x] == 'X' && isFirstPawn) {
                num++;
                isFirstPawn = false;
            }
        }
    }
    
    MaxMatching Graph(num, num);
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            if (board[y][x] == '.') {
                Graph.addAdj(hmap[y][x], vmap[y][x]);
            }
        }
    }

    cout << Graph.run();
    // debugV2D(hmap);
    // debugV2D(vmap);
    return 0;
}