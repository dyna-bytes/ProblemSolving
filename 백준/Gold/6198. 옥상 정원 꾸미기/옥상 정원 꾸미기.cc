#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
typedef pair<int, int> pii;
typedef long long ll;

int N;
int H[80000];

ll solve() {
    stack<int> S; // 내림차순 모노톤 스택
    ll ans = 0;
    for (int i = 0; i < N; i++) {
        while (!S.empty() && S.top() <= H[i]) {
            S.pop();
            ans += S.size(); // 방금 pop된 건물을 볼 수 있는 앞쪽 건물의 개수
        }
        S.push(H[i]);
    }

    while (!S.empty()) {
        S.pop();
        ans += S.size();
    }
    return ans;
}

int main() {
    FASTIO;
    cin >> N;
    for (int i = 0; i < N; i++) cin >> H[i];
    cout << solve();
    return 0;
}