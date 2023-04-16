#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
typedef vector<int> vint;

int N, K;
vint A(10);

void input() {
    cin >> N >> K;
    A.resize(N);
    for (int& a: A) cin >> a;

    reverse(A.begin(), A.end());
}

int greedy() {
    int ret = 0;
    for (int a: A) {
        if (K < a) continue;
        else {
            int x = K / a;
            K -= x * a;
            ret += x;
        }
    }

    return ret;
}

int main() {
    FASTIO;
    input();
    cout << greedy();
    return 0;
}