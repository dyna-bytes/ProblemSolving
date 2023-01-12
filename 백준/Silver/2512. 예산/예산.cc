#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
typedef long long ll;
const int MAXN = 1e5 + 1;

int N, M;
ll requests[MAXN];
ll max_money;

bool isPossible(ll limit) {
    ll total = 0;
    for (int i = 0; i < N; i++) 
        total += (requests[i] > limit ? limit : requests[i]);
    
    return total <= M;
}

ll lowerBound() {
    ll lo = 0, hi = max_money + 1;
    while (lo + 1 < hi) {
        ll mid = (lo + hi) / 2;
        if (isPossible(mid)) lo = mid;
        else hi = mid;
    }
    return lo;
}

int main() {
    FASTIO;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> requests[i];
        max_money = max(max_money, requests[i]);
    }
    cin >> M;

    cout << lowerBound();
    return 0;
}