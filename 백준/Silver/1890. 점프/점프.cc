#if 1
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#ifndef ONLINE_JUDGE
#define FL "[" << __func__ << "](" << __LINE__ << ") "
#define dbg(x) cout << "[DEBUG]" << FL << #x << " is " << x << endl;
#else
#define dbg(x)
#endif // !ONLINE_JUDGE

typedef long long ll;
typedef vector<ll> vll;

int N;
vector<vll> board;
vector<vll> memo;

inline bool inRange(int y, int x) {
    return 0 <= y && y < N && 0 <= x && x < N;
}

ll f(int y, int x) {
    if (!inRange(y, x)) return 0;
    if (y == N - 1 && x == N - 1) return 1;

    ll& ret = memo[y][x];
    if (ret != -1) return ret;

    ll jump = board[y][x];
    if (jump == 0) return ret = 0;

    return ret = f(y + jump, x) + f(y, x + jump);
}

#ifndef ONLINE_JUDGE
int __main() {
#else
int main() {
#endif // !ONLINE_JUDGE
    FASTIO;
    cin >> N;
    board = vector<vll>(N, vll(N));
    memo = vector<vll>(N, vll(N, -1));
    for (int y = 0; y < N; ++y)
        for (int x = 0; x < N; ++x)
            cin >> board[y][x];

    cout << f(0, 0) << endl;
    return 0;
}

#ifndef ONLINE_JUDGE
int main() {
    freopen("prob1890_input.txt", "r", stdin);
    for (int TC = 0; TC < 1; TC++)
        __main();
    return 0;
}
#endif // !ONLINE_JUDGE
#endif // 1
