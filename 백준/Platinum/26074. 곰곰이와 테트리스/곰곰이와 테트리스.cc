#include <bits/stdc++.h>
#define FASTIO cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(0)
#define endl '\n'
using namespace std;

int main() {
    FASTIO;
    int N, M;

    cin >> N >> M;

    if ((N == 1 && M == 2) || (N == 2 && M == 1))
        cout << "ChongChong" << endl;
    else
        cout << "GomGom" << endl;

    return 0;
}