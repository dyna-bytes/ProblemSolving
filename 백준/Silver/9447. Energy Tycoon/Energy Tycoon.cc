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

ll solve(int n, string& s) {
    ll ret = 0;
    int one = 0;
    int two = 0;
    int area = 0;

    for (char c: s) {
        int x = c - '0';

        if (x == 1) {
            if (area + 1 <= n) {
                one++;
                area++;
            } else if (two) {
                two--;
                one++;
                area--;
            }
        } else if (x == 2) {
            if (area + 2 <= n) {
                two++;
                area += 2;
            }
        }

        ret += one + two;
    }

    return ret;
}

int main() {
    FASTIO;
    int n;
    cin >> n;
    string s;
    cin >> s;

    cout << solve(n, s) << endl;
    return 0;
}