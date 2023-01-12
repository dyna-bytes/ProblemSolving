#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
typedef pair<int, int> pii;
typedef vector<int> vint;

int N, M;
int priority_table[10];
deque<pii> dq;
void input() {
    cin >> N >> M;
    dq = {};
    fill(priority_table, priority_table + 10, 0);
    for (int i = 0; i < N; i++) {
        int priority; cin >> priority;
        dq.push_back({ priority, i });
        priority_table[priority]++;
    }
}

int solve() {
    auto higherExist = [&](int priority) {
        for (int pr = priority + 1; pr < 10; pr++)
            if (priority_table[pr]) return true;
        return false;
    };

    int cnt = 0;
    while (!dq.empty()) {
        auto [priority, idx] = dq.front();
        dq.pop_front();

        if (higherExist(priority)) dq.push_back({priority, idx});
        else {
            priority_table[priority]--;
            cnt++;
            if (idx == M) return cnt;
        }
    }
    return 0;
}

int main() {
    FASTIO;
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        input();
        cout << solve() << endl;
    }
    return 0;
}