#include <iostream>
#include <bits/stdc++.h>

using namespace std;
#define endl '\n'
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
//#define DBG
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

bool isAakaraka(const string& str) {
    debug(str);
    int n = str.size();
    if (n <= 1) return true;

    int m = n / 2;
    int l = m, r = m;
    if ((n & 1) == 0) l--;

    for (; 0 <= l && r < n; l--, r++)
        if (str[l] != str[r]) return false;

    if ((n & 1) == 0)
        return isAakaraka(str.substr(0, m)) && isAakaraka(str.substr(m));

    return isAakaraka(str.substr(0, m)) && isAakaraka(str.substr(m + 1));
}

int main() {
    FASTIO;
    string str;
    cin >> str;

    bool ret = isAakaraka(str);
    if (ret) cout << "AKARAKA" << endl;
    else cout << "IPSELENTI" << endl;
    return 0;
}