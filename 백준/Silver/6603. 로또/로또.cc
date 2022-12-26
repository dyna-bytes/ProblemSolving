#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'

int N;
int R = 6;
int S[50];
int used[50];
int ans[50];

void nCr(int curr = 0, int count = 0) {
    if (count == R) {
        for (int i = 0; i < R; i++) cout << ans[i] << " ";
        cout << endl;
        return;
    }

    for (int next = curr; next < N; next++) { 
        if (used[next]) continue;
        used[next] = true;
        ans[count] = S[next];

        nCr(next, count + 1);
        used[next] = false;
    }
}


int main() {
    FASTIO;
    while (true) {
        cin >> N;
        if (N == 0) break;

        for (int i = 0; i < N; i++) cin >> S[i];
        nCr();
        cout << endl;
    }
    return 0;
}