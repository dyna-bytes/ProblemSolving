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
const int MAXN = 300 + 5;

int steps[MAXN];
int dp[MAXN][2]; // {index, contiguous}
// dp[n+1][1] = steps[n+1] + dp[n][0]
// dp[n+2][0] = steps[n+1] + max(dp[n][1], dp[n][0])

int f(int N) {
    fill(dp[0], dp[0] + MAXN, 0);
    fill(dp[1], dp[1] + MAXN, 0);

    dp[1][0] = steps[1];
    dp[1][1] = 0;

    dp[2][0] = steps[2];
    dp[2][1] = dp[1][0] + steps[2];


    for (int i = 3; i <= N; i++) {
        dp[i][1] = steps[i] + dp[i-1][0];
        dp[i][0] = max(dp[i][0],
            steps[i] + max(dp[i-2][1], dp[i-2][0]));
    }

    return max(dp[N][0], dp[N][1]);
}

int main() {
    FASTIO;
    int N;
    cin >> N;
    for (int i = 1; i <= N; i++)
        cin >> steps[i];

    cout << f(N) << endl;
    return 0;
}