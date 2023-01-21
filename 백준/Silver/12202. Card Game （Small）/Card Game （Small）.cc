#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
const int INF = 1e9;

int N, K;
list<int> cards;

int solve() {
    cin >> N >> K;
    cards = {};
    for (int i = 0; i < N; i++) {
        int a; cin >> a;
        cards.push_back(a);
    }
    while (true) {
        bool erased = false;
        for (auto it = cards.begin(); it != cards.end(); ++it) {
            int a = *it;
            int b = (next(it) == cards.end()) ? INF : *next(it);
            int c = (next(it) == cards.end() || next(next(it)) == cards.end()) ? INF : *next(next(it));

            if (c - b == K && b - a == K) {
                it = cards.erase(it);
                it = cards.erase(it);
                it = cards.erase(it);
                erased = true;
            }
        }

        if (!erased) break;
    }
    return cards.size();
}
int main() {
    FASTIO;
    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        cout << "Case #" << t << ": ";
        cout << solve() << endl;
    }

    return 0;
}