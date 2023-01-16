#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define debug(x) cout << "[debug] " << #x << " is " << x << endl
typedef pair<int, int> pii;
typedef vector<pii> vpii;
const int INF = 1e9 + 1;

int N;
vpii cows;
unordered_map<int, int> idDB;
int total_ids;

int solve() {
    total_ids = idDB.size();
    idDB = {};
    sort(cows.begin(), cows.end());
    int min_range = INF;

    idDB[cows[0].second] = 1;
    // 구간 (s, e]에 모든 품종이 있는지 검사
    for (int s = 0, e = 0; s <= e; ) {   
        if (e < N && idDB.size() < total_ids) {
            idDB[cows[++e].second]++;
        } else {
            if (--idDB[cows[s].second] == 0)
                idDB.erase(cows[s].second);
            s++;
        }

        if (s < e && e < N && idDB.size() == total_ids) {
            min_range = min(min_range, cows[e].first - cows[s].first);
        }
    }

    // N = 1일 때 예외처리
    if (min_range == INF) min_range = 0;
    return min_range;
}
int main() {
    FASTIO;
    cin >> N;
    cows.resize(N);
    for (auto& [x, id]: cows) {
        cin >> x >> id;
        idDB[id] = true;
    }
    cout << solve();
    return 0;
}