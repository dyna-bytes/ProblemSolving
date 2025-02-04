#include <bits/stdc++.h>
#define FASTIO cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(0)
#define endl '\n'
using namespace std;

int solve(int countA, int countB, int maxA, int maxB) {
    if (maxA == 0 || maxB == 0) {
        return min(countA, maxA) + min(countB, maxB);
    }

    if (countA < countB) {
        swap(countA, countB);
        swap(maxA, maxB);
    }

    int len = 0;
    while (true) {
        len += min(countA, maxA);
        countA = max(countA-maxA, 0);

        if (!countB) break;

        len += min(countB, 1);
        countB = max(countB-1, 0);
    }
    return len;
}

int main() {
    FASTIO;
    int countA, countB, maxA, maxB;
    cin >> countA >> countB >> maxA >> maxB;
    cout << solve(countA, countB, maxA, maxB) << endl;

    return 0;
}