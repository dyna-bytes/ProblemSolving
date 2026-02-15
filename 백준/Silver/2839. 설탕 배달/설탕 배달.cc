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

const int INF = 1e9;
vector<int> dp;
int f(int n) {
    if (n < 0) return INF;
    else if (n == 0) return 0;

    int& ret = dp[n];
    if (ret != -1) return ret;

    ret = min(1 + f(n - 5), 1 + f(n - 3));
    return ret;
}
int solve(int N) {
    dp.resize(N + 1, -1);

    int ret = f(N);
    if (ret >= INF) return -1;
    return ret;
}

int main() {
    FASTIO;

    int N;
    cin >> N;
    cout << solve(N) << endl;
    return 0;
}