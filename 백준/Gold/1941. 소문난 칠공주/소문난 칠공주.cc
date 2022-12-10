#include <stdio.h>
#include <cstring>
#define ABS(x) (((x) < 0) ? -(x) : (x))
#define MAXN 5
const int dy[] = {-1, 1, 0, 0}, dx[] = {0, 0, -1, 1};

int A[MAXN * MAXN] = {
    0, 1, 2, 3, 4,
    5, 6, 7, 8, 9,
    10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 
    20, 21, 22, 23, 24
};
int used[MAXN * MAXN];
int selected[MAXN * MAXN];

const int N = MAXN * MAXN;
const int R = 7;
const int S = 4;

int board[MAXN][MAXN];
int visited[MAXN][MAXN];

bool inRange(int y, int x) {
    return 0 <= y && y < MAXN && 0 <= x && x < MAXN;
}
int dist(int y, int x, int ny, int nx) {
    return ABS(y - ny) + ABS(x - nx);
}
int dfs(int y, int x) {
    int ret = 1;
    for (int i = 0; i < R; i++) {
        int ny = selected[i] / MAXN, nx = selected[i] % MAXN;
        if (dist(y, x, ny, nx) != 1) continue;
        if (visited[ny][nx]) continue;
        visited[ny][nx] = true;
        ret += dfs(ny, nx);
    }
    return ret;
}

int ans = 0;
void nCr(int n = -1, int r = 0) {
    if (r == R) {
        int s_cnt = 0;
        for (int i = 0; i < R; i++) s_cnt += (board[selected[i]/MAXN][selected[i]%MAXN] == 'S');
        if (s_cnt < S) return;
        
        int y = selected[0] / MAXN, x = selected[0] % MAXN;
        visited[y][x] = true;
        if (dfs(y, x) == R) ans++;
        memset(visited, 0, sizeof(visited));
        return;
    }

    for (int m = n + 1; m < N; m++) {
        if (used[m]) continue;
        used[m] = true;
        selected[r] = A[m];
        nCr(m, r + 1);
        used[m] = false;
    }
}

int main() {
    for (int y = 0; y < MAXN; y++)
        for (int x = 0; x < MAXN; x++)
            scanf(" %c", &board[y][x]);
    nCr();
    printf("%d\n", ans);
    return 0;
}