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


const ll edges[6] = {1, 1, 1, 1, 2, 1};

ll solve(ll n) {
    ll k = (n - 1)/6;
    ll m = (n - 1)%6;

    ll sum = 0;
    for (int i = 0; i < m; i++)
        sum += (edges[i] + k);

    // SUM{ 6k + 1 } [k = 0 to N] = 3k^2 + 4k + 1
    sum += (3*k*k + 4*k + 1);
    return sum;
}

int main() {
    FASTIO;
    ll n;
    cin >> n;
    cout << solve(n) << endl;
    return 0;
}