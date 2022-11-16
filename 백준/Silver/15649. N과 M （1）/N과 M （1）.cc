#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef vector<int> vint;
#define endl '\n'

int N, R;
vint A;
vint used;

void nPr(int depth) {
    if (depth == R) {
        for (int i = 0; i < R; i++) cout << A[i] + 1 << " ";
        cout << endl;
        return;
    }

    for (int i = 0; i < N; i++) {
        if (used[i]) continue;
        used[i] = true;
        A[depth] = i;

        nPr(depth + 1);

        used[i] = false;
    }
}

int main() {
    cin >> N >> R;

    A.resize(N + 1);
    used.resize(N + 1);
    nPr(0);
    return 0;
}