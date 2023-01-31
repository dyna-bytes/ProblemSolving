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
#define debug2DIter(vv) do{\
    cout << "[debug] " << #vv << endl;\
    for (auto v: vv) {\
        for (auto e: v) cout << e << " | ";\
        cout << endl;\
    }\
}while(0)
typedef pair<int, int> pii;
typedef vector<int> vint;
#define MINE -1

int N;
vector<vint> board;
vector<vint> visited;
bool inRange(int y, int x) {
    return 0 <= y && y < N && 0 <= x && x < N;
}

void input() {
    cin >> N;
    board = visited = {};
    board.resize(N, vint(N)); visited.resize(N, vint(N));
    for (int y = 0; y < N; ++y)
        for (int x = 0; x < N; ++x) {
            char ch; cin >> ch;
            if (ch == '*') board[y][x] = MINE;
        }
}

void preprocess() {
    for (int y = 0; y < N; ++y) 
        for (int x = 0; x < N; ++x) {
            if (board[y][x] == MINE) continue;

            int mines = 0;
            for (int r = y - 1; r <= y + 1; ++r)
                for (int c = x - 1; c <= x + 1; ++c) {
                    if (!inRange(r, c)) continue;
                    if (board[r][c] == MINE) mines++;
                }

            board[y][x] = mines;
        }
}

// search if near neighbors are 0, and check them visited
void dfs(int y, int x) {
    for (int ny = y - 1; ny <= y + 1; ++ny) 
        for (int nx = x - 1; nx <= x + 1; ++nx) {
            if (!inRange(ny, nx)) continue;
            if (board[ny][nx] == MINE) continue;
            if (visited[ny][nx]) continue;
            visited[ny][nx] = true;

            if (board[ny][nx] == 0) dfs(ny, nx);
        }
}

int solve() {
    int clicks = 0;
    for (int y = 0; y < N; ++y)
        for (int x = 0; x < N; ++x) {
            if (board[y][x] == 0 && !visited[y][x]) {
                visited[y][x] = true;
                dfs(y, x);
                clicks++;
            } 
        }

    for (int y = 0; y < N; ++y)
        for (int x = 0; x < N; ++x) {
            if (board[y][x] == MINE) continue;
            if (visited[y][x]) continue;
            visited[y][x] = true;
            clicks++;
        }
    return clicks;
}

int main() {
    FASTIO;
    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        cout << "Case #" << t << ": ";
        input();
        preprocess();
        cout << solve() << endl;
    }
}