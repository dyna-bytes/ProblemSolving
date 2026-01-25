#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
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
typedef pair<ll, ll> pll;

template <typename T>
std::vector<T> operator+=(std::vector<T>& a, std::vector<T>& b)
{
    assert(a.size() == b.size());

    std::transform(a.begin(), a.end(), b.begin(),
                   a.begin(), std::plus<T>());
    return a;
}

bool is_executable(const vector<ll>& need, const vector<ll>& avail) {
    for (size_t i = 1; i < need.size(); ++i)
        if (need[i] > avail[i]) return false;

    return true;
}

bool safety_check(ll P,
        vector<ll> avails,
        vector<vector<ll>>& needs,
        vector<vector<ll>>& allocs)
{
    vector<bool> done(P + 1, 0);
    ll dones = 0;
    while (true) {
        ll proc = -1;
        for (ll i = 1; i <= P; i++) {
            if (done[i]) continue;
            if (!is_executable(needs[i], avails)) continue;
            proc = i;
            break;
        }

        if (proc == -1)
            return dones == P;

        avails += allocs[proc];
        done[proc] = true;
        dones++;
    }
    return false;
}

ll resource_request(ll P, ll R, ll K,
        vector<ll> avails,
        vector<vector<ll>> needs,
        const vector<pll>& requests)
{
    vector<vector<ll>> allocs(P + 1, vector<ll>(R + 1, 0));
    vector<bool> finished(P + 1, false);

    for (ll t = 0; t < K; t++) {
        auto [p, r] = requests[t];

        if (finished[p]) return false;

        avails[r]--;
        allocs[p][r]++;
        needs[p][r]--;

        if (avails[r] < 0) return false;

        bool is_done = true;
        for (int r = 1; r <= R; r++) {
            if (needs[p][r] > 0) {
                is_done = false;
                break;
            }
        }

        if (is_done) {
            for (int r = 1; r <= R; r++) {
                avails[r] += allocs[p][r];
                allocs[p][r] = 0;
            }
            finished[p] = true;
        }
    }

    return safety_check(P, avails, needs, allocs);
}

ll solve(ll P, ll R, ll T,
        const vector<ll>& avails,
        const vector<vector<ll>>& needs,
        const vector<pll>& requests)
{
    ll s = 0;
    ll e = T + 1;
    while (s + 1 < e) {
        ll m = (s + e)/2;

        if (resource_request(P, R, m, avails, needs, requests)) s = m;
        else e = m;
    }

    if (s == T) return -1;
    return s + 1;
}

int main() {
    ll P, R, T;
    cin >> P >> R >> T;
    vector<ll> avails(R + 1);
    for (ll r = 1; r <= R; r++) cin >> avails[r];

    vector<vector<ll>> needs(P + 1, vector<ll>(R + 1));
    for (ll p = 1; p <= P; p++)
        for (ll r = 1; r <= R; r++) cin >> needs[p][r];

    vector<pll> requests(T);
    for (pll& request: requests)
        cin >> request.first >> request.second;

    ll ret = solve(P, R, T, avails, needs, requests);
    cout << ret << endl;

    return 0;
}