#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define debug(x) cout << "[debug] " << #x << " is " << x << endl
const double CAPACITY = 250.0;
const int MAXN = 1 << 17;

int B, L, N;
double glasses[401][MAXN]; // [level][n]   (n: 와인 잔의 번호)

/**
 * @param {int} level 현재 층
 * @param {int} num_glass 현재 층에 있는 와인 잔의 개수
 */
void flowWine(int level=1, int num_glass=1) {
    if (level == L) return;

    int n = 1; // 와인 잔의 번호
    bool allGlassesEmpty = true;
    for (int y = 1; y <= level; ++y) {
        for (int x = 0; x < y; ++x, ++n) {
            if (glasses[level][n] > CAPACITY) {
                double leftover = glasses[level][n] - CAPACITY;
                glasses[level][n] = CAPACITY;

                glasses[level + 1][n] += leftover/3;
                glasses[level + 1][n + y] += leftover/3;
                glasses[level + 1][n + y + 1] += leftover/3;

                allGlassesEmpty = false;
            }
        }
    }

    if (!allGlassesEmpty) flowWine(level + 1, level + 1 + num_glass);
}

void solve() {
    cin >> B >> L >> N;
    for (int level = 1; level <= L; ++level)
        for (int n = 1; n <= N; ++n)
            glasses[level][n] = 0;

    glasses[1][1] = B * 750.0;
    flowWine();
    cout << min(glasses[L][N], CAPACITY) << endl;
}

int main() {
    FASTIO;
    cout << fixed;
    cout.precision(7);
    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}