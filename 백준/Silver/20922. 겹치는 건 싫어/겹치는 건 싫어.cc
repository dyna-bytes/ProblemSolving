#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
const int MAXN = 2e5 + 1;
const int INF = 1e5 + 1;
#define debug(x) cout << "[debug] " << #x << " is " << x << endl

int N, K;
int A[MAXN];
int count[MAXN];
int main() {
    FASTIO;
    cin >> N >> K;
    for (int i = 0; i < N; i++) cin >> A[i];
    int max_len = 0;
    int s = 0;
    for (int e = 0; e < N; e++) {
        if (++::count[A[e]] > K) {
            max_len = max(max_len, e - s);
            while (::count[A[e]] > K && s < e) --::count[A[s++]];
        }
    }
    if (::count[A[N - 1]] <= K) max_len = max(max_len, N - s);
    cout << max_len;
    return 0;
}