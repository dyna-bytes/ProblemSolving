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

int solve(int Y, int X, int K, vector<vector<int>>& board) {
    vector<vector<int>> pref_y(Y + 1, vector<int>(X + 1, 0));
    vector<vector<int>> pref_x(Y + 1, vector<int>(X + 1, 0));

    for (int y = 0; y < Y; y++)
        for (int x = 0; x < X; x++)
            pref_x[y][x + 1] = pref_x[y][x] + board[y][x];

    for (int x = 0; x < X; x++)
        for (int y = 0; y < Y; y++)
            pref_y[y + 1][x] = pref_y[y][x] + board[y][x];

    int ret = 0;
    int target_sum = 2 * K + 1;

    for (int y = K; y < Y - K; y++) {
        for (int x = K; x < X - K; x++) {
            // Horizontal check: from x-K to x+K
            int horizontal = pref_x[y][x + K + 1] - pref_x[y][x - K];
            // Vertical check: from y-K to y+K
            int vertical = pref_y[y + K + 1][x] - pref_y[y - K][x];

            if (horizontal == target_sum && vertical == target_sum) 
                ret++;
        }
    }
    return ret;
}

int main() {
    FASTIO;
    int Y, X;
    cin >> Y >> X;
    int K;
    cin >> K;

    vector<vector<int>> board(Y, vector<int>(X));
    for (int y = 0; y < Y; y++)
        for (int x = 0; x < X; x++)
            cin >> board[y][x];

    cout << solve(Y, X, K, board) << endl;
    return 0;
}