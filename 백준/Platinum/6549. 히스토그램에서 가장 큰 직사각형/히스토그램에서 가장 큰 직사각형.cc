#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define debug(x) cout << "[debug] " << #x << " is " << x << endl
typedef long long ll;
typedef pair<ll, ll> pll;
const int MAXN = 1e5 + 1;
const int INF = 1e9 + 1;
#define HEIGHT first
#define INDEX second

int N;
ll H[MAXN];

int input() {
    cin >> N;
    if (N == 0) return false;
    for (int i = 0; i < N; i++) cin >> H[i];
    return true;
}

ll solve() {
    stack<pll> stk; // 내림차순 모노톤 스택
    ll max_rect = 0;
    ll height;
    for (int i = 0; i < N; i++) {
        height = INF;
        while (!stk.empty() && stk.top().HEIGHT >= H[i]) {
            height = min(height, stk.top().HEIGHT);
            stk.pop();
            ll width = i - (stk.empty() ? -1 : stk.top().INDEX) - 1;
            max_rect = max(max_rect, height * width);
        }

        stk.push({ H[i], i });
    }

    while (!stk.empty()) {
        height = min(height, stk.top().HEIGHT);
        stk.pop();
        ll width = N - (stk.empty() ? -1 : stk.top().INDEX) - 1;
        max_rect = max(max_rect, height * width);
    }

    return max_rect;
}

int main() {
    FASTIO;
    while (input()) {
        cout << solve() << endl;
    }
    return 0;
}