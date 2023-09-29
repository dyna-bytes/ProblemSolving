#if 1
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#ifndef ONLINE_JUDGE
#define dbg(x) cout << "[DEBUG] " << #x << " is " << x << endl
#else
#define dbg(x)
#endif // ONLINE_JUDGE

typedef vector<int> vint;

int solve(int N, int K, vint& sensors) {
    sort(sensors.begin(), sensors.end());
    
    vint diff;
    for (int i = 0; i < N - 1; i++)
        diff.push_back(sensors[i + 1] - sensors[i]);
    sort(diff.begin(), diff.end());

    int sum = 0;
    int m = (int)diff.size() - (K - 1); // 남은 diff가 K-1개가 되어야 함.
    dbg(diff.size());
    dbg(m);
    for (int i = 0; i < m; i++) {
        dbg(diff[i]);
        sum += diff[i];
    }
    
    
    return sum;
}

int main() {
    FASTIO;
    int N, K;
    cin >> N >> K;
    vint sensors(N);
    for (auto& sensor : sensors) cin >> sensor;

    cout << solve(N, K, sensors);
}
#endif