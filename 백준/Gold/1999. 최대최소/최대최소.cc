#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define MAXN 251
int N, B, K;
int A[MAXN][MAXN];
int mins[MAXN][MAXN];
int maxs[MAXN][MAXN];

int main() {
    FASTIO;
    cin >> N >> B >> K;
    for (int y = 0; y < N; y++)
        for (int x = 0; x < N; x++)
            cin >> A[y][x];

    for (int y = 0; y < N - B + 1; y++)
        for (int x = 0; x < N - B + 1; x++) {
            mins[y][x] = 251;
            for (int r = y; r < y + B; r++)
                for (int c = x; c < x + B; c++) {
                    mins[y][x] = min(mins[y][x], A[r][c]);
                    maxs[y][x] = max(maxs[y][x], A[r][c]);
                }
        }

    for (int i = 0; i < K; i++) {
        int y, x; 
        cin >> y >> x;
        y--, x--;
        cout << maxs[y][x] - mins[y][x] << endl;
    }
    return 0;
}