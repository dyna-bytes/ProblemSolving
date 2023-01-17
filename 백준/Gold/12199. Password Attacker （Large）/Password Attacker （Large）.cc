#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
typedef long long ll;
const ll MOD = 1e9 + 7;
const int MAXN = 101;
int M, N;
ll dp[MAXN][MAXN];

ll f(int n, int m) {
    ll& ret = dp[n][m];
    if (ret) return ret;
    if (m == 1) return ret = 1;

    if (n == m) return ret = f(n-1, m-1) * m % MOD;
    return ret = (f(n-1, m-1) + f(n-1, m)) * m % MOD;
}

int main() {
    FASTIO;
    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        cin >> M >> N;
        cout << "Case #" << t << ": ";
        cout << f(N, M) << endl;
    }
    return 0;
}