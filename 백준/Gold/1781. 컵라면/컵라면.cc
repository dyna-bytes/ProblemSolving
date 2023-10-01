#if 1
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
typedef pair<int, int> pii;
typedef vector<int> vint;
typedef vector<pii> vpii;

#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define FL "[" << __func__  << "](" << __LINE__ << ") "
#ifndef ONLINE_JUDGE
#define dbg(x) cout << "[DEBUG]" << FL << #x << " is " << x << endl;
#else
#define dbg(x)
#endif // !ONLINE_JUDGE

int solve(int N, auto pq) {
    int num_ramen = 0;
    int day = 1;
    
    priority_queue<int, vint, greater<int>> bucket;

    while (!pq.empty()) {
        auto [deadline, ramen] = pq.top(); pq.pop();
        
        if (day <= deadline) {
            bucket.push(ramen);
            day++;
        } else if (bucket.top() < ramen) {
            bucket.pop();
            bucket.push(ramen);
        }
    }

    while (!bucket.empty()) {
        auto ramen = bucket.top(); bucket.pop();
        dbg(ramen);
        num_ramen += ramen;
    }
    return num_ramen;
}

#ifndef ONLINE_JUDGE
int __main() {
#else
int main() {
#endif // !ONLINE_JUDGE
    FASTIO;
    int N;
    cin >> N;

    auto cmp = [](pii& a, pii& b) {
        if (a.first == b.first) return a.second < b.second;
        return a.first > b.first;
    };
    priority_queue<pii, vpii, decltype(cmp)> pq(cmp);
    for (int i = 0; i < N; i++) {
        int deadline, ramen;
        cin >> deadline >> ramen;
        pq.push({ deadline, ramen });
    }

    cout << solve(N, pq) << endl;
    return 0;
}

#ifndef ONLINE_JUDGE
int main() {
    freopen("prob1781_input.txt", "r", stdin);
    for (int TC = 0; TC < 3; TC++)
        __main();
    return 0;
}
#endif // !ONLINE_JUDGE

#endif