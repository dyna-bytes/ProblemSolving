#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
typedef long long ll;
const int MAXN = 1e5 + 1;

int N;
ll A[MAXN];

ll solve() {
    ll max_sum = -MAXN;
    ll cur_sum = 0;
    for (int i = 0; i < N; i++) {
        cur_sum = max(A[i], cur_sum + A[i]);
        max_sum = max(max_sum, cur_sum);
    }
    return max_sum;
}
int main() {
    FASTIO;
    cin >> N;
    for (int i = 0; i < N; i++) cin >> A[i];
    cout << solve();
    return 0;
}