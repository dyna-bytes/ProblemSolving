#include <iostream>
#include <bits/stdc++.h>

using namespace std;
#define endl '\n'
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define DBG
#ifdef DBG
#define debug(x) cout << "[" << __func__ << "](" << __LINE__ << ") " << #x << " is " << x << endl;
#define debugVect(v) do { \
    cout << "[" << __func__ << "](" << __LINE__ << ") " << #v << " is |\t"; \
    for (auto e: v) cout << e << "|\t" ; \
    cout << endl; \
} while (0)
#define debugVect2d(vv) do { \
    cout << "[" << __func__ << "](" << __LINE__ << ") " << #vv << " is " << endl; \
    for (auto v: vv) debugVect(v); \
} while (0)
#else
#define debug(x)
#define debugVect(v)
#define debugVect2d(vv)
#endif

void solve(int N, int M, vector<vector<int>>& keyinput) {
    sort(keyinput.begin(), keyinput.end());

    for (vector<int>& key: keyinput)
        cout << (char)key[2];
}

int main() {
    FASTIO;
    int N, M;
    cin >> N >> M;
    vector<vector<int>> keyinput(M, vector<int>(3, 0));
    for (vector<int>& key: keyinput) {
        int a;
        int b;
        char c;
        cin >> a >> b >> c;
        key[0] = b;
        key[1] = a;
        key[2] = c;
    }

    solve(N, M, keyinput);
    return 0;
}