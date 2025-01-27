#include <bits/stdc++.h>
#define FASTIO cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(0)
#define endl '\n'
using namespace std;

int main() {
    FASTIO;

    int N;
    cin >> N;
    cout << ((N % 2) ? "Goose" : "Duck") << endl;
    return 0;
}