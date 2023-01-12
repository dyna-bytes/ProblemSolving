#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define debug(x) cout << "[debug] " << #x << " is " << x << endl
typedef long long ll;
const int MAXN = 1e4 + 1;

int N;
ll A[MAXN];

ll solve() {
    ll ans = 0;
    for (int i = 0; i < N - 2; i++) {
        for (int s = i + 1, e = N - 1; s < e; ) {
            if (A[i] + A[s] + A[e] < 0) s++;
            else if (A[i] + A[s] + A[e] > 0) e--;
            else { 
                if (A[s] == A[e]) {
                    ans += (e - s);
                    s++;
                    continue;
                }

                ll dup_left = 1;
                ll dup_right = 1;
                for (; A[s] == A[s + 1]; s++) dup_left++;
                for (; A[e] == A[e - 1]; e--) dup_right++;
                ans += dup_left * dup_right; // count duplicated pairs
                s++;
                e--;
            }
        }
    }
    return ans;
}
int main() {
    FASTIO;
    cin >> N;
    for (int i = 0; i < N; i++) cin >> A[i];
    sort(A, A + N);
    cout << solve();
    return 0;
}