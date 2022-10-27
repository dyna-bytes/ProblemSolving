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

#define EMPTY 0
#define WALL 1
const int MAXL = 1001;
const int dy[] = { -1, 1, 0, 0 }, dx[] = { 0, 0, -1, 1 };

vector<vint> board(MAXL, vint(MAXL));
vector<vint> visited_fire(MAXL, vint(MAXL));
vector<vint> visited_man(MAXL, vint(MAXL));
int Y;
int X;

inline bool inRange(int y, int x) {
    return y >= 0 && y < Y && x >= 0 && x < X;
}

void bfs_fire(queue<pii>& q_fire) {
    while (!q_fire.empty()) {
        auto [y, x] = q_fire.front(); q_fire.pop();

        for (int d = 0; d < 4; d++) {
            int ny = y + dy[d], nx = x + dx[d];
            if (!inRange(ny, nx)) continue;
            if (board[ny][nx] == WALL) continue;
            if (visited_fire[ny][nx]) continue;

            visited_fire[ny][nx] = visited_fire[y][x] + 1;
            q_fire.push({ ny, nx });
        }
    }
}

int bfs_man(queue<pii>& q_man) {
    bool escaped = false;
    while (!q_man.empty()) {
        auto [y, x] = q_man.front(); q_man.pop();

        for (int d = 0; d < 4; d++) {
            int ny = y + dy[d], nx = x + dx[d];
            if (!inRange(ny, nx)) {
                escaped = true;
                return visited_man[y][x];
            }

            if (board[ny][nx] == WALL) continue;
            if (visited_man[ny][nx]) continue;
            if (visited_fire[ny][nx] && visited_fire[ny][nx] <= visited_man[y][x] + 1) continue;

            visited_man[ny][nx] = visited_man[y][x] + 1;
            q_man.push({ ny, nx });
        }
    }

    return -1;
}

void solve(queue<pii>& q_fire, queue<pii>& q_man) {
    bfs_fire(q_fire);
    int ret = bfs_man(q_man);
    if (ret == -1) cout << "IMPOSSIBLE" << endl;
    else cout << ret << endl;
}

void input(queue<pii>& q_fire, queue<pii>& q_man) {
    cin >> X >> Y;
    board.clear();
    board.resize(Y, vint(X));

    visited_fire.clear();
    visited_fire.resize(Y, vint(X));

    visited_man.clear();
    visited_man.resize(Y, vint(X));

    for (int y = 0; y < Y; y++) {
        string str; cin >> str;
        for (int x = 0; x < X; x++) {
            if (str[x] == '.') board[y][x] = EMPTY;
            else if (str[x] == '#') board[y][x] = WALL;
            else if (str[x] == '@') {
                board[y][x] = EMPTY;
                q_man.push({ y, x });
                visited_man[y][x] = 1;
            } else if (str[x] == '*') {
                board[y][x] = EMPTY;
                q_fire.push({ y, x });
                visited_fire[y][x] = 1;
            }
        }   
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int T; cin >> T;
    while (T--) {
        queue<pii> q_fire, q_man;
        input(q_fire, q_man);
        solve(q_fire, q_man);
    }
    return 0;
}