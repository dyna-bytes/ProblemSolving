#include <iostream>
#include <bits/stdc++.h>

using namespace std;
#define endl '\n'
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define DBG
#ifdef DBG
#define debug(x) cout << "[" << __func__ << "](" << __LINE__ << ") " << #x << " is " << x << endl;
#define debugVect(v) do { \
    cout << "[" << __func__ << "](" << __LINE__ << ") " << #v << " is |\t"; \
    for (auto e: v) cout << e << "|\t" ; \
    cout << endl; \
} while (0)
#define debugVect2d(vv) do { \
    cout << "[" << __func__ << "](" << __LINE__ << ") " << #vv << " is " << endl; \
    for (auto v: vv) debugVect(v); \
} while (0)
#else
#define debug(x)
#define debugVect(v)
#define debugVect2d(vv)
#endif
typedef long long ll;
/**
 * A = 1
 * B = 2
 * Z = 26
 * AA = 27
 * AZ = 52
 * BA = 53
 * BZ = 78
 */

void solve(ll R, ll C) {
    string res;

    while (C > 26) {
        --C;
        int m = C % 26;
        C = C / 26;
        res.push_back(m + 'A');
    }
    res.push_back(--C + 'A');
    reverse(res.begin(), res.end());
    cout << res << R << endl;
}

int main() {
    FASTIO;
    string s;
    ll R, C;

    while (true) {
    cin >> s;
        int c_idx = s.find('C');
        R = stoll(s.substr(1, c_idx));
        C = stoll(s.substr(c_idx + 1));
        if (R == 0 && C == 0) break;

        solve(R, C);
    }


    return 0;
}