#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false), cin.tie(NULL);
#define endl '\n'

int main() {
    FASTIO;
    int N; cin >> N;
    string s = to_string(N);
    sort(s.begin(), s.end(), greater<int>());
    cout << s << endl;
    return 0;
}