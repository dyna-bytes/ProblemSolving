#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
// #define DBG
#ifdef DBG
#define debug(x) cout << "[" << __func__ << "](" << __LINE__ << ") " << #x << " is " << x << endl;
#else
#define debug(x)
#endif

int round(int n, int t, int s,
        vector<int>& count, vector<int>& dead)
{
    int curr = s;
    while (t--) {
        debug(curr);
        while (dead[curr])
            curr = (curr + 1) % n;

        count[curr]++;
        curr = (curr + 1) % n;
    }
    int prev = (curr - 1 + n) % n;
    dead[prev] = true;
    return curr;
}

int equal(int n, vector<int>& count, vector<int>& dead, int& alive) {
    int cnt = -1;
    alive = 0;
    for (int i = 0; i < n; i++) {
        if (dead[i]) continue;
        alive++;
        if (cnt == -1) cnt = count[i];
        else if (cnt != count[i]) return 0;
    }
    return cnt;
}

void solve(int n, int t) {
    vector<int> count(n, 0);
    vector<int> dead(n, 0);

    int p, c;
    int s = 0;
    do {
       s = round(n, t, s, count, dead);
       debug(s);
    } while((c = equal(n, count, dead, p)) == 0);
    cout << p << " " << c << endl;
}

int main() {
    FASTIO;
    while (true) {
        int N, T;
        cin >> N;
        if (N == 0) break;
        cin >> T;

        solve(N, T);
    }

    return 0;
}