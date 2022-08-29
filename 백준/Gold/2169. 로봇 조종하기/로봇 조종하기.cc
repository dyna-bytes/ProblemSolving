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
        if(v[y].empty()){ std::cout << "  []\n"; continue; } \
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
typedef vector<int> vint;
typedef vector<pii> vpii;
const int dy[] = {0, 0, 1}, dx[] = {-1, 1, 0}; // 좌, 우, 하
const int IMPOSSIBLE = -2e9 - 1;
#define LEFT 0
#define RIGHT 1

int Y, X;
vector<vint> grid;
vector<vint> visited;
vector<vector<vint>> dp; 
bool inRange (int y, int x) { return y >= 0 && y < Y && x >= 0 && x < X; }

int f(int y, int x, int prev_dir) {
    if (y == Y-1 && x == X-1) return grid[y][x];

    int& ret = dp[y][x][prev_dir];
    if (ret != IMPOSSIBLE) return ret;

    for (int dir = 0; dir < 3; dir++) {
        int ny = y + dy[dir], nx = x + dx[dir];
        if (!inRange(ny, nx)) continue;
        if (visited[ny][nx]) continue;
        // if (dir == LEFT && prev_dir == RIGHT) continue;
        // if (dir == RIGHT && prev_dir == LEFT) continue;

        visited[ny][nx] = true;
        ret = max(ret, f(ny, nx, dir) + grid[y][x]);
        visited[ny][nx] = false;        
    }
    
    return ret;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> Y >> X;
    grid.resize(Y+1, vint(X+1));
    dp.resize(Y+1, vector<vint>(X+1, vint(3, IMPOSSIBLE)));
    visited.resize(Y+1, vint(X+1));
    for (int y = 0; y < Y; y++)
        for (int x = 0; x < X; x++)
            cin >> grid[y][x];
            
    visited[0][0] = true;
    cout << f(0, 0, 2) << endl;
    // debugV2D(dp);
    return 0;
}