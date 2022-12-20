#include <stdio.h>
const int dy[] = {-1, 1, 0, 0}, dx[] = {0, 0, -1, 1};

int Y, X, K;
bool inRange(int y, int x) { return 0 <= y && y < Y && 0 <= x && x < X; }
int visited[6][6];
int available[6][6];

int dfs(int y, int x, int k) {
    if (y == 0 && x == X - 1) return (k == K);

    int ret = 0;
    for (int d = 0; d < 4; d++) {
        int ny = y + dy[d], nx = x + dx[d];
        if (!inRange(ny, nx)) continue;
        if (!available[ny][nx]) continue;
        if (visited[ny][nx]) continue;
        
        visited[ny][nx] = true;
        ret += dfs(ny, nx, k + 1);
        visited[ny][nx] = false;
    }
    return ret;
}

int main() {
    scanf(" %d %d %d", &Y, &X, &K);
    for (int y = 0; y < Y; y++) {
        char str[6]; scanf("%s", str);
        for (int x = 0; x < X; x++) {
            if (str[x] == '.') available[y][x] = true;
        }
    }

    visited[Y - 1][0] = true;
    printf("%d", dfs(Y - 1, 0, 1));

    return 0;
}