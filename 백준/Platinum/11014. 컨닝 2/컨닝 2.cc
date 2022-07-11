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
const int dy[] = {-1, 0, 1, 1, 0, -1}, dx[] = {-1, -1, -1, 1, 1, 1}; // CCW. ↖←↙↘→↗

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
    void addAdj(int a, int b){
        adj[a].push_back(b);
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
    bool canMatch(int a){
        if (visited[a]) return false;
        visited[a] = true;
        for(int b: adj[a]){
            if(B[b] == -1 || canMatch(B[b])){
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
            if(A[a] == -1){
                fill(visited.begin(), visited.end(), 0);
                if(canMatch(a)) match++;
            }
        }
        return match;
    }
};

int Y, X; 
vector<vector<char>> board(80, vector<char>(80));

bool inRange(int y, int x){ return y >= 0 && y < Y && x >= 0 && x < X; }
int node(int y, int x){ return y*X + x; }

// edge generator
void dfs(int y, int x, MaxMatching& Graph){
    if (y == Y) return;
    if (board[y][x] == '.'){
        for(int d = 0; d < 6; d++){
            int ny = y + dy[d], nx = x + dx[d];
            if (!inRange(ny, nx)) continue;
            if (board[ny][nx] == 'x') continue;
            Graph.addAdj(node(y, x), node(ny, nx));
        }
    }
    dfs(y+1, x, Graph);
}
void solve(){
    cin >> Y >> X;

    int total_seats = 0;
    board.clear();
    board.resize(Y, vector<char>(X));

    for(int y = 0; y < Y; y++)
        for(int x = 0; x < X; x++){
            cin >> board[y][x];
            if (board[y][x] == '.') total_seats++;
        }

    MaxMatching Graph(Y*X+1, Y*X+1);
    for(int x = 0; x < X; x++){
        if(x%2 == 1) dfs(0, x, Graph);    
    }
    cout << total_seats - Graph.run() << endl;
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