#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
typedef long long ll;
const ll mod = 1e9 + 7;

ll M, N;
int used[8];

ll dfs(int n) {
    if (n == N) {
        for (int m = 0; m < M; m++)
            if (!used[m]) return false;
        return true;
    }

    ll ret = 0;
    for (int m = 0; m < M; m++) {
        used[m]++;
        (ret += dfs(n+1)) %= mod;
        used[m]--;
    }
    return ret;
}

ll solve() {
    for (int i = 0; i < 8; i++) used[i] = 0;
    return dfs(0);
}

int main() {
    FASTIO;
    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        cin >> M >> N;
        cout << "Case #" << t << ": ";
        cout << solve() << endl;
    }
    return 0;
}