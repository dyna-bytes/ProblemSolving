#include <bits/stdc++.h>
using namespace std;
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
typedef pair<int, int> pii;

int solve(int N, priority_queue<pii>& pq) {
    int ret = 0;
    multiset<int> team; // team[n]: 인원이 n인 팀
    while (!pq.empty()) { // 큰 [h, k] 부터 팀 지정
        auto [h, k] = pq.top(); pq.pop();

        int s = -1, e = k;
        // team[n] 에서 n < k 인 가장 큰 n을 찾음
        while (s + 1 < e) {
            int mid = (s + e)/2;
            auto it = team.upper_bound(mid); 
            if (it != team.end() && *it < k) s = mid;
            else e = mid;
        }

        if (s == -1) {
            team.insert(1);
            ret++;
        } else {
            team.erase(team.find(s+1)); // s+1 = n < k
            team.insert(s+2);
        }
    }

    return ret;
}

int main() {
    fastio;

    int N; cin >> N;
    priority_queue<pii> pq;

    for (int i = 0; i < N; i++) {
        int h, k; cin >> h >> k;
        pq.push({h, k});
    }
    cout << solve(N, pq);
    return 0;
}