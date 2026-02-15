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

ll solve(ll N, vector<ll>& A) {
    ll ret = 0;
    sort(A.begin(), A.end(), greater<ll>());

    ll S = 1;
    ll sum = A[0];

    int i;
    for (i = 1; i < N; i++) {
        if (sum + S * A[i] > 0) {
            S++;
            sum += A[i];
        } else
            break;
    }

    ret = sum * S;
    ret += accumulate(A.begin() + i, A.end(), 0LL);
    return ret;
}

int main() {
    FASTIO;
    int N;
    cin >> N;
    vector<ll> A(N);
    for (auto& a: A) cin >> a;

    cout << solve(N, A) << endl;
    return 0;
}