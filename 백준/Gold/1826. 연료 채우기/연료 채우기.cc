#if 1
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#ifndef ONLINE_JUDGE
#define FL "[" << __func__ << "](" << __LINE__ << ") "
#define dbg(x) cout << "[DEBUG]" << FL << #x << " is " << x << endl;
#define EXPECT_EQ(A, B) do { \
    auto a = A, b = B; \
    if (a != b) cout << "[DEBUG]" << FL << a << " != " << b << endl; \
} while (0)
#else
#define dbg(x)
#define EXPECT_EQ(A, B)
#endif // !ONLINE_JUDGE
typedef pair<int, int> pii;
typedef vector<int> vint;
typedef vector<pii> vpii;

/*
* * 사실 주유소의 위치보다 주유소의 연료량이 더 중요하다.
*   (정차는 주유소의 위치에서 하는데, 도달할 수 있는 최대 거리는 총 연료량 합 만큼임)
* 
* 최소 기준: 도달 가능한 주유소 중 가장 많은 연료를 가진 주유소만 거침.
* 최대 기준: (도달 가능한) 모든 주유소를 다 거침.
* 중간 기준: 최소 기준으로 목적지에 도착할 수 있는지 보고,
*   불가능하다면 점점 최대 기준에 가까워지도록 거치는 주유소를 늘림.
*   남은 주유소 중 가장 연료가 많은 주유소를 선택함.
*/
int solve(int N, int L, int P, auto & stations) {
    int fuel = P;
    int num_stops = 0;
    priority_queue<int> reachable;

    while (fuel < L) {
        while (!stations.empty() && fuel >= stations.top().first) {
            auto [a, b] = stations.top(); 
            stations.pop();
            reachable.push(b);
            dbg(b);
        }
        if (!reachable.empty()) {
            fuel += reachable.top();
            reachable.pop();
            num_stops++;
        } else if ((stations.empty() && fuel < L) ||
            (!stations.empty() && fuel < stations.top().first)) return -1;

        dbg(fuel);
    }
    return num_stops;
}

#ifndef ONLINE_JUDGE
int __main() {
#else
int main() {
#endif // !ONLINE_JUDGE
    int N;
    cin >> N;
    auto cmp = [](pii& a, pii& b) {
        if (a.first == b.first) return a.second < b.second;
        return a.first > b.first;
    };
    priority_queue<pii, vpii, decltype(cmp)> stations(cmp);
    int a, b;
    for (int i = 0; i < N; i++) {
        cin >> a >> b;
        stations.push({ a, b });
    }
    int L, P;
    cin >> L >> P;

    int ans = solve(N, L, P, stations);
    cout << ans << endl;
#ifndef ONLINE_JUDGE
    return ans;
#else
    return 0;
#endif // !ONLINE_JUDGE
}

#ifndef ONLINE_JUDGE
int main() {
    freopen("prob1826_input.txt", "r", stdin);
    for (int TC = 0; TC < 6; ++TC) {
        dbg(TC);
        int res = __main();
        int ans; cin >> ans;
        EXPECT_EQ(res, ans);
        cout << endl;
    }
    return 0;
}
#endif // !ONLINE_JUDGE

#endif // 1
