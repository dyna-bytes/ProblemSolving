#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vint;
typedef vector<ll> vll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;

#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#define endl '\n';
#define debug(x) cout << "[Debug] " << #x << " is " << x << endl;
#define _debugV1(v) for (auto it = v.begin(); it != v.end(); ++it) { cout << *it; if (next(it) != v.end()) cout << " | "; }
#define debugVec(v) do { \
    cout << "[Debug] [ "; \
    _debugV1(v); \
    cout << " ]" << endl; \
} while (0)
#define debugV2(v) do { \
    cout << "[Debug] [" << endl; \
    for (auto v1: v) { \
        cout << "  [ "; \
        _debugV1(v1); \
        cout << " ]" << endl; \
    } \
    cout << "]" << endl; \
} while (0)
#define pair_out(pair) cout << '{' << pair.first << ", " << pair.second << '}'

pll solve(int N, vll &liquids) {
    int lo = 0, hi = N-1;
    int LO = 0, HI = N-1;
    ll min_acid = LLONG_MAX;
    while (lo < hi) {
        ll acid = liquids[lo] + liquids[hi];
        if (min_acid >= abs(acid)) {
            min_acid = abs(acid);
            LO = lo, HI = hi;
        }
        if (acid > 0) hi--;
        else lo++;
    }
    return {liquids[LO], liquids[HI]};
}

int main() {
    FASTIO;

    int N; cin >> N;
    vll liquids(N);
    for (auto &liquid: liquids) cin >> liquid;
    pll ret = solve(N, liquids);
    cout << ret.first << " " << ret.second;
    return 0;
}