#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vint;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define debug(x) cout << "[debug] " << #x << " is " << x << endl
#define debugVec(v) do{\
    cout << "[debug] " << #v << endl;\
    for (auto e: v) cout << e << " | ";\
    cout << endl;\
}while(0)
#define debugV2D(vv) do{\
    cout << "[debug] " << #vv << endl;\
    for (auto v: vv) {\
        for (auto e: v) cout << e << " | ";\
        cout << endl;\
    }\
    cout << endl;\
}while(0)

const vector<vint> cost = {
    {10, 8, 7, 5, 0, 1},
    {8, 6, 4, 3, 0, 1},
    {7, 4, 3, 2, 0, 1},
    {5, 3, 2, 2, 0, 1},
    {0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 0, 0}
};

int Y, X; 
vector<vint> board;
vector<vint> dp;

/**
 * y = idx / X
 * x = idx % X
 * status MSB : board[y][x]의 상태 (현재 인덱스의 위치)
 * status LSB : board[y-1][x+1]의 상태 (현재 인덱스 우상단의 위치)
 */
int f(int idx, int status) {
    if (idx == Y*X) return 0;
    int y = idx / X;
    int x = idx % X;

    int& ret = dp[idx][status];
    if (ret != -1) return ret;

    // 블록을 놓지 않는 경우
    ret = f(idx + 1, status >> 1);

    // 1x2 가로 시도
    if ((x != X - 1) && ((status & 0b11) == 0)) 
        ret = max(ret, cost[board[y][x]][board[y][x+1]] + f(idx + 2, status >> 2));
    
    // 2x1 세로 시도
    if (y != Y - 1 && ((status & 0b1) == 0)) 
        ret = max(ret, cost[board[y][x]][board[y+1][x]] + f(idx + 1, (status >> 1 | (1 << (X - 1)))));
    
    return ret;
}

int main() {
    FASTIO;
    cin >> Y >> X;
    board.resize(Y + 1, vint(X + 1));
    dp.resize(Y*X + 1, vint(pow(2, X + 1), -1));

    for (int y = 0; y < Y; y++)
        for (int x = 0; x < X; x++) {
            char ch; cin >> ch;
            board[y][x] = ch - 'A';
        }

    cout << f(0, 0);
    return 0;
}