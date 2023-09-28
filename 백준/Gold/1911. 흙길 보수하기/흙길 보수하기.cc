#if 1
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'

typedef pair<int, int> pii;
typedef vector<int> vint;
typedef vector<pii> vpii;

int solve(int N, int L, vpii& pools) {
    sort(pools.begin(), pools.end());

    int pos = 0;
    int cnt = 0;
    for (auto [s, e] : pools) {
        if (pos < s) pos = s;
        while (pos < e) {
            pos += L;
            cnt++;
        }
    }
    return cnt;
}

int main() {
    FASTIO;
    int N, L;
    cin >> N >> L;

    vpii pools(N);
    for (auto& [s, e] : pools)
        cin >> s >> e;
    cout << solve(N, L, pools);
    return 0;
}

#endif