#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define endl '\n'
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

int K;
vector<set<int>> dp(8 + 1);

int op(int A, int B, int type) {
    switch (type) {
        case 0: return A + B; break;
        case 1: return A - B; break;
        case 2: return A * B; break;
        default: if (B) {return A/B;} break;
    }
}

// 길이가 x인 K-표현의 집합. x개의 K를 써서 만들 수 있는 모든 값.
set<int> monodigital(int x) {
    if (x == 0) return {};
    if (x == 1) return {K};

    set<int> &ret = dp[x];
    if (ret.size() > 1) return ret;
       
    for (int len = 1; len < x; len++) 
        for (int A: monodigital(len)) 
            for (int B: monodigital(x - len)) 
                for (int p = 0; p < 4; p++) {
                    int r = op(A, B, p);
                    if (r > 0) ret.insert(r);
                }

    return ret;
}

void query(int a) {
    for (int x = 1; x <= 8; x++) 
        if (dp[x].find(a) != dp[x].end()) {
            cout << x << endl;
            return;
        }

    cout << "NO" << endl;
}

int main() {
    fastio;

    cin >> K;
    // fill trivial cases
    int dec = 0;
    for (int i = 1; i <= 8; i++) {
        dec += K;
        dp[i].insert(dec);
        dec *= 10;
    }

    for (int x = 1; x <= 8; x++)
        monodigital(x);

    int Q; cin >> Q;
    for (int i = 0; i < Q; i++) {
        int a; cin >> a;
        query(a);
    }
    return 0;
}