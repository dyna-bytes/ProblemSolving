#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'

int N, K;
string number;

void solve() {
    int k = 0;
    deque<int> stk;
    for (char n: number) {
        while (!stk.empty() && stk.back() < n && k < K) {
            stk.pop_back();
            k++;
        }

        stk.push_back(n);
    }

    while (stk.size() > N - K) stk.pop_back();
    for (char c: stk) cout << c;
}

int main() {
    FASTIO;
    cin >> N >> K;
    cin >> number;
    solve();
    return 0;
}