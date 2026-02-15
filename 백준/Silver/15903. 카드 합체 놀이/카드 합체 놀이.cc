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
ll solve(int n, int m, vector<ll>& A) {
    priority_queue<ll, vector<ll>, greater<ll>> pq(A.begin(), A.end());

    while (m-- > 0) {
        ll x = pq.top(); pq.pop();
        ll y = pq.top(); pq.pop();

        pq.push(x + y);
        pq.push(x + y);
    }

    ll ret = 0;
    while (pq.size()) {
        ret += pq.top();
        pq.pop();
    }
    return ret;
}

int main() {
    FASTIO;
    int n, m;
    cin >> n >> m;

    vector<ll> A(n);
    for (ll& a: A) cin >> a;

    cout << solve(n, m, A) << endl;
    return 0;
}