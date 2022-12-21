#include <bits/stdc++.h>
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int S[28];
string base = "moo";
void f(int k, int n) {
    if (k == 0) {
        cout << base[n];
        return;
    }

    if (n < S[k - 1]) {
        f(k - 1, n);
    } else if (n < S[k - 1] + (k + 3)) {
        if (n == S[k - 1]) cout << 'm';
        else cout << 'o';
        return;
    } else {
        f(k - 1, n - (S[k - 1] + (k + 3)));
    }
}
int main() {
    FASTIO;
    int N; cin >> N;
    
    int k = 0;
    int size = 3;
    S[0] = 3;
    while (size < N) {
        k++;
        size = 2 * size + (k + 3);
        S[k] = size;
    }
    f(k, N - 1);
    return 0;
}