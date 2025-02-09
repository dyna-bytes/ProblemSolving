#include <bits/stdc++.h>
#define FASTIO cin.tie(0)->sync_with_stdio(0)
#define endl '\n'
using namespace std;

int main() {
    FASTIO;
    int N; cin >> N;
    vector<pair<int,int>> coordinates(N);

    for (int i = 0; i < N; i++)
        cin >> coordinates[i].first >> coordinates[i].second;

    int max_sum = INT_MIN, min_sum = INT_MAX;
    int max_diff = INT_MIN, min_diff = INT_MAX;
    for (int i = 0; i < N; i++) {
        auto &coord = coordinates[i];
        int sum = coord.first + coord.second;
        int diff = coord.first - coord.second;

        max_sum = max(max_sum, sum);
        min_sum = min(min_sum, sum);
        max_diff = max(max_diff, diff);
        min_diff = min(min_diff, diff);
    }

    int ans = max(max_sum - min_sum, max_diff - min_diff);
    cout << ans << endl;

    return 0;
}