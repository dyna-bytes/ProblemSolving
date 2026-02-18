#include <iostream>
#include <bits/stdc++.h>

using namespace std;

#define FASTIO ios_base::sync_with_stdio(false), cin.tie(NULL);
#define endl '\n'

typedef long long ll;

ll solve(ll k, ll d, ll a, vector<vector<ll>>& missions) {
    ll ret = 0;
    for (auto& mission: missions) {
        ll donation = mission[0] * k - mission[1] * d + mission[2] * a;
        if (donation < 0) continue;
        ret += donation;
    }
    return ret;
}

int main() {
    FASTIO;
    int N; cin >> N;
    while (N-- > 0) {
        int M; cin >> M;
        vector<vector<ll>> missions(M);
        for (ll i = 0; i < M; ++i) {
            ll K, D, A;
            cin >> K >> D >> A;
            missions[i] = {K, D, A};
        }
        ll k, d, a;
        cin >> k >> d >> a;
        cout << solve(k, d, a, missions) << endl;
    }
    return 0;
}