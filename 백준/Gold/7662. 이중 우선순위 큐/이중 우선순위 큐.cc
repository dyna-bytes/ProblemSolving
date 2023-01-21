#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
typedef vector<pii> vpii;

#define endl '\n'
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

void solve (int k, vpii& cmds) {
    multiset<int> ms;

    for (auto [op, q]: cmds) {
        if (op == 0) ms.insert(q);
        else if (op == 1 && !ms.empty()) ms.erase(prev(ms.end()));
        else if (op == 2 && !ms.empty()) ms.erase(ms.begin());
    }

    if (ms.empty()) {
        cout << "EMPTY" << endl;
        return;
    }

    cout << *prev(ms.end()) << " " << *ms.begin() << endl;
}

int main() {
    fastio;
    int T; cin >> T;
    while (T--) {
        int k; cin >> k;
        vpii cmds(k);
        for (int i = 0; i < k; i++) {
            char op; cin >> op;
            int q; cin >> q;

            if (op == 'D') {
                if (q == 1) cmds[i] = {1, -1};
                else if (q == -1) cmds[i] = {2, -1};
            } else if (op == 'I') {
                cmds[i] = {0, q};
            }
        }

        solve(k, cmds);
    }
    return 0;
}