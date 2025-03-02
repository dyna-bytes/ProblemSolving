#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define FASTIO cin.tie(0)->sync_with_stdio(0)
typedef long long ll;

ll pow(ll A, ll B, ll mod) {
    if (B == 1) return A % mod;
    if (B == 0) return 1;

    ll square = pow(A, B/2, mod);
    if (B % 2)
        return ((square * square) % mod * A) % mod;
    else
        return (square * square) % mod;
}

int main() {
    FASTIO;
    ll A, B, C;
    cin >> A >> B >> C;
    cout << pow(A, B, C) << endl;

    return 0;
}
