#include <bits/stdc++.h>
#define FASTIO cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(0)
#define endl '\n'
using namespace std;

int main() {
    FASTIO;
    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        if (N <= 3) cout << 0 << endl;
        else if (N == 4) cout << 2 << endl;
        else if (N == 5) cout << 1 << endl;
        else if (N == 6) cout << 0 << endl;
        else cout << 1 << endl;
    }
    return 0;
}