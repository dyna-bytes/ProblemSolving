#include <iostream>
#include <bits/stdc++.h>

using namespace std;
#define endl '\n'
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define DBG
#ifdef DBG
#define debug(x) cout << "[" << __func__ << "](" << __LINE__ << ") " << #x << " is " << x << endl;
#define debugVect(v) do { \
    cout << "[" << __func__ << "](" << __LINE__ << ") " << #v << " is |\t"; \
    for (auto e: v) cout << e << "|\t" ; \
    cout << endl; \
} while (0)
#define debugVect2d(vv) do { \
    cout << "[" << __func__ << "](" << __LINE__ << ") " << #vv << " is " << endl; \
    for (auto v: vv) debugVect(v); \
} while (0)
#else
#define debug(x)
#define debugVect(v)
#define debugVect2d(vv)
#endif

typedef pair<int, int> pii;
const int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, -1, 1};

int solve(int Y, int X, int ty, int tx, vector<vector<int>>& board) {
    auto inRange = [&](int y, int x) {
        return 0 <= y && y < Y && 0 <= x && x < X;
    };
    vector<vector<int>> visited(Y, vector<int>(X, 0));
    queue<pii> q;

    q.push({ty, tx});
    visited[ty][tx] = true;

    while (q.size()) {
        auto [y, x] = q.front(); q.pop();

        for (int d = 0; d < 4; ++d) {
            int ny = y + dy[d], nx = x + dx[d];
            if (!inRange(ny, nx)) continue;
            if (visited[ny][nx]) continue;
            if (board[ny][nx] >= board[y][x]) {
                visited[ny][nx] = true;
                q.push({ny, nx});
            }
        }
    }

    int ret = 0;
    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            if ((y == 0 || y == Y - 1 || x == 0 || x == X - 1) && visited[y][x]) {
                ret++;
            }
        }
    }
    return ret;
}

int main() {
    FASTIO;
    int T; cin >> T;

    for (int t = 1; t <= T; t++) {
        int Y, X;
        cin >> Y >> X;
        int ty, tx;
        cin >> ty >> tx;
        ty--, tx--;

        vector<vector<int>> board(Y, vector<int>(X));
        for (int y = 0; y < Y; ++y)
            for (int x = 0; x < X; ++x)
                cin >> board[y][x];

        int ret = solve(Y, X, ty, tx, board);
        cout << "Case #" << t << ": " << ret << endl;
    }

    return 0;
}