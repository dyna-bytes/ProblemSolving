#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
typedef pair<int, int> pii;
#define X first
#define Y second

unordered_map<int, set<pii>> pos_grad_set; // { k, { { x0, y0 }, { x1, y1 }, ... } } where k = y - x
unordered_map<int, set<pii>> neg_grad_set; // { k, { { x0, y0 }, { x1, y1 }, ... } } where k = y + x

int N, K;
string path;
pii curr = { -1, -1 };

void input() {
    cin >> N >> K;
    cin >> path;
    int x, y;
    for (int i = 0; i < N; i++) {
        cin >> x >> y;
        pos_grad_set[y - x].insert({ x, y });
        neg_grad_set[y + x].insert({ x, y });
        if (curr == pii{ -1, -1 }) curr = { x, y };
    }
}

// A: 우상
// B: 우하
// C: 좌상
// D: 좌하
void solve() {
    for (char dir: path) {
        set<pii>& pos_line = pos_grad_set[curr.Y - curr.X];
        set<pii>& neg_line = neg_grad_set[curr.Y + curr.X];
        set<pii>& line = (dir == 'A' || dir == 'D') ? pos_line : neg_line;

        auto now = line.find(curr);
        if ((dir == 'C' || dir == 'D') && now == line.begin()) continue;

        auto dest = (dir == 'A' || dir == 'B') ? next(now) : prev(now);
        if ((dir == 'A' || dir == 'B') && dest == line.end()) continue;

        pos_line.erase(curr);
        neg_line.erase(curr);
        curr = *dest;
    }
    cout << curr.X << ' ' << curr.Y;
}

int main() {
    FASTIO;
    input();
    solve();
    return 0;
}