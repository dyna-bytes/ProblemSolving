#include <bits/stdc++.h>
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef unsigned long long ull;
#define debug(x) cout << "[debug] " << #x << " is " << x << endl

int main() {
    FASTIO;
    ull A, B;
    cin >> A >> B;

    ull ans = A;
    if (!(A & 1ULL) && B - A >= 3) {
        A += 3ULL;
        ans = 0;
    }

    ull mod = (B - A) & 0b11;
    ull dummy = (B - A) - mod;

    for (ull i = dummy + 1; i <= B - A; i++) {
        ans ^= (A + i);
    }
    
    cout << ans;
    return 0;
}