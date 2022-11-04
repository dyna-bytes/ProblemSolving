#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vint;
typedef vector<ll> vll;

#define endl '\n'
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

int P, Q;
unordered_map<ll, ll> dp;

ll f(ll n) {
    auto it = dp.find(n);
    if (it != dp.end()) return it->second;

    if (n == 0) return 1;

    ll ret = f(n/P) + f(n/Q);
    dp.insert({n, ret});
    return ret;    
}

int main() {
    fastio;

    ll N; 
    cin >> N >> P >> Q;

    cout << f(N);
    return 0;
}