#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define debug(x) cout << "[debug] " << #x << " is " << x << endl
typedef pair<int, int> pii;
const int MAXN = 65535;

inline pii bitHandler(int bits) {
    int p = (bits >> 16) & 0XFFFF;
    int q = bits & 0xFFFF;
    return { p, q };
}

inline int pairHandler(const pii& p_q) {
    return (p_q.first << 16) + p_q.second;
}

int tree[MAXN + 1];
unordered_map<int, int> p_q;
void dfs(int curr=1, int p=1, int q=1) {
    if (curr > MAXN) return;
    tree[curr] = pairHandler({ p, q });
    p_q[ tree[curr] ] = curr;
    dfs(2*curr, p, p + q);
    dfs(2*curr + 1, p + q, q);
}

int main() {
    FASTIO;
    dfs();
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        int id; cin >> id;

        cout << "Case #" << (t + 1) << ": ";
        if (id == 1) {
            int n; cin >> n;
            auto [p, q] = bitHandler(tree[n]);
            cout << p << " " << q << endl;
        } else {
            int p, q; cin >> p >> q;
            int n = p_q[pairHandler({ p, q })];
            cout << n << endl;
        }
    }
    return 0;
}