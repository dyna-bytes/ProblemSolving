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
const int MAXN = 1e6 + 5;

int dp[MAXN];
int f(int N) {
    fill(dp, dp + MAXN, INF);
    dp[1] = 0;
    for (int n = 1; n <= N; n++) {
        if (3*n <= N)
            dp[3*n] = min(dp[3*n], dp[n] + 1);
        if (2*n <= N)
            dp[2*n] = min(dp[2*n], dp[n] + 1);
        if (n+1 <= N)
            dp[n+1] = min(dp[n+1], dp[n] + 1);
    }
    return dp[N];
}

int main() {
    FASTIO;
    int N;
    cin >> N;
    cout << f(N) << endl;

    return 0;
}