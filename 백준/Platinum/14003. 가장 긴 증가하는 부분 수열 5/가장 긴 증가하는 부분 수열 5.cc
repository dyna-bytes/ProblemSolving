#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<pll> vpll;
const ll INF = 1e9 + 1;

void solve(int N, vpll& A) {
    vpll dp = { {-INF, -1} };
    vll history(N+1, -1);

    for (auto [a, idx]: A) {
        if (dp.back().first < a) {
            history[idx] = dp.back().second;
            dp.push_back({a, idx});
        } else {
            auto it = lower_bound(dp.begin(), dp.end(), make_pair(a, idx), [](const pll& p1, const pll& p2) {
                return p1.first < p2.first;
            });
            history[idx] = (it-1)->second;
            *it = {a, idx};
        }
    }

    int len = dp.size() - 1;
    cout << len << endl;

    vll ans;
    for (int curr = dp[len].second; curr != -1; curr = history[curr])
        ans.push_back(A[curr].first);
    
    reverse(ans.begin(), ans.end());
    for (int a: ans) cout << a << " ";
}

int main() {
    int N; cin >> N;
    vpll A(N);
    for (int i = 0; i < N; i++) {
        int inp; cin >> inp;
        A[i] = {inp, i};
    }

    solve(N, A);

    return 0;
}