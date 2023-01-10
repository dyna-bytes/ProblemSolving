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
#define debugIterIter(vv) do{\
    cout << "[debug] " << #vv << endl;\
    for (auto v: vv) {\
        for (auto e: v) cout << e << " | ";\
        cout << endl;\
    }\
    cout << endl;\
}while(0)
typedef vector<int> vint;

int N;
vector<vint> board;
// to_horizontal: left, to_vertical: up
void forward_move(int y_or_x, bool to_vertical) {
    auto tile = [&](int p) {
        return to_vertical ? &board[p][y_or_x] : &board[y_or_x][p];
    };
    for (int s = -1, e = 0; s < N - 1; ) {
        if (s == -1 && *tile(0)) { s++; continue; }

        e = s + 1;

        while (e < N && *tile(e) == 0) e++;
        if (e == N) break;

        // shifting
        if (e != s + 1)
        for (int i = 0; i + e < N; i++) {
            *tile(s + 1 + i) = *tile(e + i);
            *tile(e + i) = 0;
        }

        if (s > - 1 && *tile(s) == *tile(s + 1)) {
            *tile(s) *= 2;
            *tile(s + 1) = 0;
            e = s + 2;
            for (int i = 0; i + e < N; i++) {
                *tile(s + 1 + i) = *tile(e + i);
                *tile(e + i) = 0;
            }
        }
        s++;
    }
}

// to_horizontal: right, to_vertical: down
void backward_move(int y_or_x, bool to_vertical) {
    auto tile = [&](int p) {
        return to_vertical ? &board[p][y_or_x] : &board[y_or_x][p];
    };
    for (int s = N, e = N - 1; s > 0; ) {
        if (s == N && *tile(N-1)) { s--; continue; }
        e = s - 1;
        
        while (e >= 0 && *tile(e) == 0) e--;
        if (e == -1) break;

        // shifting
        if (e != s - 1)
        for (int i = 0; e - i >= 0; i++) {
            *tile(s - 1 - i) = *tile(e - i);
            *tile(e - i) = 0;
        }

        if (s < N && *tile(s) == *tile(s - 1)) {
            *tile(s) *= 2;
            *tile(s - 1) = 0;
            continue;
        }
        s--;
    }

}

void solve() {
    string dir;
    cin >> N >> dir;
    board = {};
    board.resize(N, vint(N));
    for (int y = 0; y < N; ++y)
        for (int x = 0; x < N; ++x)
            cin >> board[y][x];

    if (dir == "left" || dir == "up") 
        for (int y_or_x = 0; y_or_x < N; y_or_x++)
            forward_move(y_or_x, dir == "up");
    else if (dir == "right" || dir == "down") 
        for (int y_or_x = 0; y_or_x < N; y_or_x++)
            backward_move(y_or_x, dir == "down");
    // debugIterIter(board);

    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++)
            cout << board[y][x] << " ";
        cout << endl;
    }
}
int main() {
    FASTIO;
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": " << endl;
        solve();
    }
    return 0;
}