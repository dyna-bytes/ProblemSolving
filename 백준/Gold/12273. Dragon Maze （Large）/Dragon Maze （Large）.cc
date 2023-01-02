#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define debug(x) cout << "[debug] " << #x << " is " << x << endl
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
typedef pair<int, int> pii;
typedef vector<int> vint;
typedef vector<pii> vpii;
const int dy[] = {-1, 1, 0, 0}, dx[] = {0, 0, -1, 1};

int Y, X;
int sy, sx, ey, ex;
vector<vint> board;
vector<vint> visited;
inline bool inRange(int y, int x) {
    return 0 <= y && y < Y && 0 <= x && x < X;
}

typedef tuple<int, int, pii> node; // { -dist, power, { y, x } }

int bfs() {
    priority_queue<node> pq;
    node S = {0, board[sy][sx], {sy, sx}};
    pq.push(S);
    visited[sy][sx] = true;

    while (!pq.empty()) {
        auto [dist, power, y_x] = pq.top(); pq.pop();
        auto [y, x] = y_x;
        dist = -dist;
        if (y == ey && ex == x) return power;

        for (int d = 0; d < 4; ++d) {
            int ny = y + dy[d], nx = x + dx[d];
            if (!inRange(ny, nx)) continue;
            if (board[ny][nx] == -1) continue;
            if (visited[ny][nx]) continue;

            visited[ny][nx] = true;
            pq.push({ -(dist + 1), power + board[ny][nx], { ny, nx } });
        }
    }
    return -1;
}

int main() {
    FASTIO;
    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        cin >> Y >> X;
        cin >> sy >> sx >> ey >> ex;

        board = {};
        visited = {};
        board.resize(Y, vint(X));
        visited.resize(Y, vint(X));
        for (int y = 0; y < Y; ++y)
            for (int x = 0; x < X; ++x)
                cin >> board[y][x];

        cout << "Case #" << t << ": ";
        int res = bfs();
        if (res == -1) cout << "Mission Impossible." << endl;
        else cout << res << endl;
    }
    return 0;
}