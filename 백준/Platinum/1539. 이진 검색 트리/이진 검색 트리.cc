#include <bits/stdc++.h>
using namespace std;
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
typedef long long ll;
typedef vector<ll> vll;

int N;
vll height;
set<ll> ordered_tree;

ll insert(ll x) {
    auto it = ordered_tree.lower_bound(x);
    ll left = (it != ordered_tree.begin()) ? height[*prev(it)] : 0;
    ll right = (it != ordered_tree.end()) ? height[*it] : 0;

    height[x] = max(left, right) + 1;
    ordered_tree.insert(x);

    return height[x];
}

int main() {
    fastio;
    cin >> N;
    height.resize(N);

    ll res = 0;
    for (int i = 0; i < N; i++) {
        ll x; cin >> x;
        res += insert(x);
    }
    
    cout << res;

    return 0;
}