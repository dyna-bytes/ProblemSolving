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

int solve(vector<vector<int>>& segments) {
    int ret = 0;
    ret += (accumulate(segments[0].begin(), segments[0].end(), 0));

    for (int i = 1; i < segments.size(); ++i) {
        ret -= (accumulate(segments[i].begin(), segments[i].end(), 0));
    }
    return ret;
}

int main() {
    FASTIO;
    string s;
    cin >> s;

    vector<vector<int>> segments = {{ 0 }};
    for (int i = 0, j = 0; i < s.size(); ) {
        j = i;
        while (j < s.size() && (s[j] != '+' && s[j] != '-'))
            j++;

        string ss = s.substr(i, j - i);
        segments.back().push_back(stoi(ss));

        if (s[j] == '-')
            segments.push_back(vector<int>());

        i = j + 1;
    }

    cout << solve(segments) << endl;

    return 0;
}