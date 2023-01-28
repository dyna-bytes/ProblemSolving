#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define debug(x) cout << "[debug] " << #x << " is " << x << endl
typedef unsigned long long ull;
const int MAXN = 210;

int N;
ull K;
ull dp[MAXN][MAXN];

// g(n, r): coverage. n번째 자리에서 아직 닫히지 않은 "("이 r개인 집합의 크기
ull g(int n, int leftPar) {
    ull& ret = dp[n][leftPar];
    if (ret != ULLONG_MAX) return ret;
    if (leftPar < 0) return ret = 0;
    if (n == N) return leftPar == 0;
    
    ret = min(K + 100, g(n + 1, leftPar + 1) + g(n + 1, leftPar - 1));
    return ret;
}

void f(int n, int leftPar, ull k) {
    if (n == N) return;

    ull coverage = g(n + 1, leftPar + 1);
    if (coverage > k) {
        cout << '(';
        f(n + 1, leftPar + 1, k);
    } else {
        cout << ')';
        f(n + 1, leftPar - 1, k - coverage);
    }
}

void solve() {
    for (int i = 0; i < MAXN; ++i)
        for (int j = 0; j < MAXN; ++j) 
            dp[i][j] = ULLONG_MAX;

    cin >> N >> K;
    N *= 2;
    K--;

    if (K >= g(0, 0)) cout << "Doesn't Exist!";
    else f(0, 0, K);
    cout << endl;
}

int main() {
    FASTIO;

    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}