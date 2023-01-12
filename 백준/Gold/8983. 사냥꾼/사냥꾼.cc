#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<pll> vpll;

int N, M, L;
vll shooters;
vpll animals;
/**
 * @brief 사수가 동물을 잡을 수 있는 조건
 * 사수 (x, 0)와 동물 (a, b) 사이의 거리: |x - a| + b
 * 사정거리: |x - a| + b <= L
 * Thus, a + b - L <= x <= a - b + L
 */

ll solve() {
    sort(shooters.begin(), shooters.end());
    ll killcount = 0;
    for (const auto& [x, y]: animals) {
        ll left = lower_bound(shooters.begin(), shooters.end(), x + y - L) - shooters.begin();
        ll right = upper_bound(shooters.begin(), shooters.end(), x - y + L) - shooters.begin(); 
        if (right > left) killcount++;
    }
    return killcount;
}

int main() {
    FASTIO;
    cin >> M >> N >> L;
    shooters.resize(M);
    for (ll& x: shooters) cin >> x;

    animals.resize(N);
    for (auto& [x, y]: animals) cin >> x >> y;

    cout << solve();
    return 0;
}