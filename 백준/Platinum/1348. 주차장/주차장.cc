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
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

const int dy[] = {-1, 1, 0, 0}, dx[] = {0, 0, -1, 1};

int Y, X; 
int node(int y, int x){ return y*X + x; }
bool inRange(int y, int x){ return y >= 0 && y < Y && x >= 0 && x < X; }
vector<vector<char>> board;
vector<vector<int>> visited;
vector<vector<pii>> table; // {K초, {차, 주차장}}

void bfs(int sy, int sx){
    visited.clear(), visited.resize(Y, vector<int>(X));
    queue<tiii> q;

    q.push({sy, sx, 0});
    visited[sy][sx] = true;
    while (!q.empty()) {
        auto [y, x, t] = q.front(); q.pop();

        if (board[y][x] == 'P') 
            table[t].push_back({node(sy, sx), node(y, x)});

        for (int d = 0; d < 4; d++) {
            int ny = y + dy[d], nx = x + dx[d];
            if (!inRange(ny, nx)) continue;
            if (visited[ny][nx]) continue;
            if (board[ny][nx] == 'X') continue;

            q.push({ny, nx, t+1});
            visited[ny][nx] = true;
        }
    }
}

struct MaxMatching{
    int N, M;
    vector<int> A, B;
    vector<vector<int>> adj;
    vector<int> vis;
    MaxMatching(int n, int m){
        N = n, M = m;
        A.resize(N+1, -1), B.resize(M+1, -1);
        adj.resize(N+1);
        vis.resize(N+1);
    }
    bool canMatch(int a){
        if (vis[a]) return false;
        vis[a] = true;
        for(int b: adj[a]){
            if (B[b] == -1 || canMatch(B[b])){
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
                fill(vis.begin(), vis.end(), 0);
                if(canMatch(a)) match++;
            } 
        }
        return match;
    }
    void construct(vector<vector<pii>>& table, int K){
        A.clear(), A.resize(N+1, -1);
        B.clear(), B.resize(M+1, -1);
        adj.clear(), adj.resize(N+1);
        vis.clear(), vis.resize(N+1);
        for(int k = 0; k <= K; k++){
            for(pii& p: table[k])
                adj[p.first].push_back(p.second);
        }
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> Y >> X;
    board.resize(Y, vector<char>(X));
    visited.resize(Y, vector<int>(X));
    table.resize(Y*X+1);
    for(int y = 0; y < Y; y++)
        for(int x = 0; x < X; x++)
            cin >> board[y][x];
    
    int cars = 0;
    for(int y = 0; y < Y; y++)
        for(int x = 0; x < X; x++)
            if (board[y][x] == 'C'){
                bfs(y, x);
                cars++;
            }
    
    MaxMatching Graph(Y*X+1, Y*X+1);
    int lo = 0, hi = Y*X + 1;
    while (lo + 1 < hi) {
        int mid = (lo + hi)/2;
        Graph.construct(table, mid);

        if (Graph.run() < cars) lo = mid;
        else hi = mid;
    }
    int ret = hi;//lo + 1;
    if (cars == 0) cout << 0;
    else if (ret == Y*X + 1) cout << -1;
    else cout << ret;

    return 0;
}