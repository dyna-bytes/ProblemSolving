#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define debug(x) cout << "[debug] " << #x << " is " << x << endl
#define debugIter(v) do{\
    cout << "[debug] " << #v << endl;\
    for (auto e: v) cout << e << " | ";\
    cout << endl;\
}while(0)
#define debugIter2D(vv) do{\
    cout << "[debug] " << #vv << endl;\
    for (auto v: vv) {\
        for (auto e: v) cout << e << " | ";\
        cout << endl;\
    }\
    cout << endl;\
}while(0)
#define _Y first
#define _X second
typedef pair<int, int> pii;
typedef vector<int> vint;
typedef vector<pii> vpii;
const int dy[] = {-1, 0, 0, 1}, dx[] = {0, -1, 1, 0};
const int WALL = 1;
const int START = 2;
const int END = 3;
const int INF = 1e9;

int X, Y;
bool inRange(int y, int x) { return 0 <= y && y < Y && 0 <= x && x < X; }
vector<vint> board;
vector<vpii> visited;
int bfs(pii& S, pii& E) {
    queue<pair<pii, pii>> q;
    q.push({S, {0, -1}}); // {cnt, dir}
    visited[S._Y][S._X].first = 1;
    int res = INF;
    while (!q.empty()) {
        auto [pos, cnt_n_dir] = q.front(); q.pop();
        auto [y, x] = pos;
        auto [cnt, dir] = cnt_n_dir;

        if (pos == E) {
            res = min(res, cnt);
            continue;
        }
        if (visited[y][x].first < cnt) continue;
        // if (visited[y][x].first == cnt &&
        //     visited[y][x].second == dir) continue;

        for (int d = 0; d < 4; ++d) {
            int ny = y + dy[d], nx = x + dx[d];
            if (!inRange(ny, nx)) continue;
            if (board[ny][nx] == WALL) continue; 
            if (d + dir == 3) continue;
            int next_cnt = (d == dir) ? cnt : cnt + 1;
            
            if (visited[ny][nx].first < next_cnt) continue;
            if (visited[ny][nx].first == next_cnt && 
                visited[ny][nx].second == d) continue;
            visited[ny][nx] = { next_cnt, d };
            q.push({ { ny, nx }, { next_cnt, d } });
        }
    }
    return res - 1;
}
int main() {
    FASTIO;
    cin >> X >> Y;
    board.resize(Y, vint(X));
    visited.resize(Y, vpii(X, { INF, -1 }));
    int C = 1;
    pii S, E;
    for (int y = 0; y < Y; ++y)
        for (int x = 0; x < X; ++x) {
            char inp; cin >> inp;
            if (inp == '*') board[y][x] = WALL;
            if (inp == 'C') {
                board[y][x] = ++C;
                if (C == START) S = {y, x};
                if (C == END) E = {y, x};
            }
        }
    // debugIter2D(board)
    cout << max(bfs(S, E), 0);    
    return 0;
}