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

struct MaxMatcing{
    int N, M;
    vector<int> A, B;
    vector<vector<int>> adj;
    vector<int> visited;
    MaxMatcing(int n, int m) {
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
    void addAdj(int from, int to) {
        adj[from].push_back(to);
    }
    void sortAdj() {
        for (auto v: adj) {
            sort(v.begin(), v.end());
            v.erase(unique(v.begin(), v.end()), v.end());
        }
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int Y, X, N;
    cin >> Y >> X >> N;
    vector<vector<int>> board(Y, vector<int>(X, true));
    vector<vector<int>> hmap(Y, vector<int>(X));
    vector<vector<int>> vmap(Y, vector<int>(X));

    // 빈칸 입력 받기. 문제는 빈칸이 아닌 곳에 룩을 두어야 함.
    for (int i = 0; i < N; i++) {
        int y, x;
        cin >> y >> x;
        board[y-1][x-1] = false;
    }   

    MaxMatcing Graph(Y, X);
    for (int y = 0; y < Y; y++) 
        for (int x = 0; x < X; x++)
            if (board[y][x]) Graph.addAdj(y, x);
    cout << Graph.run();
    return 0;
}