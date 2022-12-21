#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define MAXN 10
const int INF = 1e9;

int N;
int left_offset_map[MAXN * 2 + 1];
int right_offset_map[MAXN * 2 + 1];

int get_left_offset(int y, int x) {
    return (y - x) + MAXN;
}
int get_right_offset(int y, int x) {
    return y + x;
} 

int black[MAXN * MAXN + 1];
int white[MAXN * MAXN + 1];
int b;
int w;

int dfs(int rp, const int color[], const int color_size) {
    if (rp == color_size) return 0;

    int y = color[rp] / N;
    int x = color[rp] % N;
    int lo = get_left_offset(y, x);
    int ro = get_right_offset(y, x);

    int ret = dfs(rp + 1, color, color_size);
    if (!left_offset_map[lo] && !right_offset_map[ro]) {
        left_offset_map[lo] = true;
        right_offset_map[ro] = true;

        ret = max(ret, 1 + dfs(rp + 1, color, color_size));

        left_offset_map[lo] = false;
        right_offset_map[ro] = false;
    }

    return ret;
}

int main() {
    FASTIO;
    cin >> N;
    int available;
    for (int y = 0; y < N; y++)
        for (int x = 0; x < N; x++) {
            cin >> available;
            if (!available) continue;

            int y_x = y * N + x;
            (((y + x) & 1) ? black[b++] : white[w++]) = y_x;
        }

    cout << dfs(0, black, b) + dfs(0, white, w);
    return 0;
}