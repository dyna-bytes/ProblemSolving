#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<pll> vpll;

int N, M;
vpll ranges;

bool isPossible(ll dist) {
    ll cnt = 0;
    ll cow = -1;
    for (const auto [s, e]: ranges) {
        if (cow < s) cow = s;
        while (s <= cow && cow <= e) {
            cow += dist;
            cnt++;
        }
    }
    return cnt >= N;
}

ll lowerBound() {
    ll lo = 0, hi = LONG_LONG_MAX;
    while (lo + 1 < hi) {
        ll mid = (lo + hi) / 2;
        if (isPossible(mid)) lo = mid;
        else hi = mid;
    }
    return lo;
}

int main() {
    FASTIO;
    cin >> N >> M;
    ranges.resize(M);
    for (auto& [s, e]: ranges) cin >> s >> e;
    sort(ranges.begin(), ranges.end());
    
    cout << lowerBound();
    return 0;
}