#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
const int MAXN = 1e5 + 1;
const int INF = 1e9;
const int mod = 9901;

int N;
int dp[3][MAXN]; // {prev_status, y}

int f(int y, int prev_status) {
    if (y == N) return 1;

    int& ret = dp[prev_status][y];
    if (ret) return ret;

    ret = f(y + 1, 0);

    if (prev_status != 1)
        (ret += f(y + 1, 1)) %= mod;
    
    if (prev_status != 2)
        (ret += f(y + 1, 2)) %= mod;
    return ret;
}

int main() {
    FASTIO;
    cin >> N;
    cout << f(0, 0);
    return 0;
}