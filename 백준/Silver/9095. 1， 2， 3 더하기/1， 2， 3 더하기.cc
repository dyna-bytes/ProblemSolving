#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define FASTIO cin.tie(0)->sync_with_stdio(0)

#define endl '\n'
#define DEBUG
#ifdef DEBUG
#define debug(x) cout << #x << " is " << x << endl;
#define debugVect(v) do { \
    cout << #v << " is |" ; \
    for (auto i : v) cout << i << "|"; \
    cout << endl; \
} while (0)
#else
#define debug(x)
#define debugVect(v)
#endif

typedef pair<int, int> pii;
const int INF = 1e9;
const int MAXN = 12;

int dp[MAXN];
int f(int N) {
    fill(dp, dp + MAXN, 0);
    dp[1] = 1;
    dp[2] = dp[1] + 1;
    dp[3] = dp[2] + dp[1] + 1;
    for (int x = 4; x <= N; x++)
        dp[x] = dp[x-3] + dp[x-2] + dp[x-1];

    return dp[N];
}

int main() {
    FASTIO;
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        cout << f(N) << endl;
    }
    return 0;
}