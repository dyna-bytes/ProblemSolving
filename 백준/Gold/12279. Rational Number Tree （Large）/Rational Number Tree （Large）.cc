#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define debug(x) cout << "[debug] " << #x << " is " << x << endl
#define MAXL 64
#define REG register
typedef unsigned long long ull;
typedef pair<ull, ull> puu;

bool isRight[MAXL + 1];
puu get_p_q(ull N) {
    int max_level = log2(N) + 1;
    REG int level;
    for (level = max_level; N > 0; --level) {
        isRight[level] = N & 1;
        N >>= 1;
    }

    ull p = 1, q = 1;
    for (level = 2; level <= max_level; ++level) {
        if (isRight[level]) p += q;
        else q += p;
    }
    return { p, q }; 
} 

ull get_n(ull p, ull q) {
    REG int level;
    for (level = 1; !(p == 1 && q == 1); ++level) {
        if (p > q) {
            isRight[level] = true;
            p -= q;
        } else {
            isRight[level] = false;
            q -= p;
        }
    }

    ull n = 1;
    for (REG int rev = level - 1; rev > 0; --rev)
        n = n * 2 + isRight[rev];
        
    return n;
}
int main() {
    FASTIO;
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        cout << "Case #" << (t + 1) << ": ";
        int id; cin >> id;
        if (id == 1) {
            ull n; cin >> n;
            const auto& [p, q] = get_p_q(n);
            cout << p << " " << q << endl;
        } else {
            ull p, q; cin >> p >> q;
            cout << get_n(p, q) << endl;
        }
    }
    return 0;
}