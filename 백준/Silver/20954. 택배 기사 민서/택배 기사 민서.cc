#include <iostream>
#include <bits/stdc++.h>
#include <math.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false), cin.tie(NULL);
#define endl '\n'
#define debug(x) cout << #x << " is " << x << endl;
typedef long long ll;

/**
 * D(i) = (-1)^i * 2^(i/2) 일때
 * if i is even (i = 2k),
 * D(i) - D(i-1) = 2^k + 2^(k-1)
 * if i is odd (i = 2k + 1),
 * D(i) - D(i-1) = -2^(k+1)
 */

static inline bool is_pow_of_two(ll x) {
    return x & (x - 1) == 0;
}

ll solve(ll x) {
    if (x == 0) return 0;

    if (x > 0) {
        // k = ceil(log2(x))
        ll k = ceil(1LL * log2(x));

        // Total = 4 * 2^k + x - 4
        return 4 * (1LL << k) + x - 4;
    } else {
        x = -x;
        // m = ceil(log2(-x))
        ll m = ceil(1LL * log2(x));

        // Total = 6 * 2^m - (-x) - 4
        return 6 * (1LL << m) + x - 4;
    }
}

int main() {
    FASTIO;
    int T; cin >> T;
    while (T-- > 0) {
        ll x; cin >> x;
        cout << solve(x) << endl;
    }
    return 0;
}