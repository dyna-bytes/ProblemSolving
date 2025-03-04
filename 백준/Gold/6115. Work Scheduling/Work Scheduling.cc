#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define FASTIO cin.tie(0)->sync_with_stdio(0)
typedef long long ll;

#define MAX_D ll(1e9)
int main() {
    int N;
    cin >> N;

    vector<pair<ll, ll>> jobs(N);
    for (auto& [D, P]: jobs) cin >> D >> P;

    // sort jobs by deadline
    sort(jobs.begin(), jobs.end(), [](auto& a, auto& b) {
        return a.first < b.first;
    });

    priority_queue<ll, vector<ll>, greater<ll>> min_heap; // store profits
    ll total_profit = 0;

    for (auto& [D, P]: jobs) {
        min_heap.push(P);
        total_profit += P;

        if (min_heap.size() > D) { // 작업의 개수가 마감시간 D를 초과하는지 비교
            total_profit -= min_heap.top();
            min_heap.pop();
        }
    }
    cout << total_profit << endl;

    return 0;
}