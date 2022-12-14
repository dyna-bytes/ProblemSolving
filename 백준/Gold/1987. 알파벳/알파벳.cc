#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAXN 20
const int dy[] = { -1, 1, 0, 0 }, dx[] = { 0, 0, -1,1 };
template <class T> const T& max(const T& a, const T& b) {
    return (a > b) ? a : b;
}


int Y, X;
char board[MAXN][MAXN];
int hash[26 + 'a'];

bool inRange(int y, int x) { return 0 <= y && y < Y && 0 <= x && x < X; }
int dfs(int y, int x) {

    int ret = 0;
    for (int d = 0; d < 4; d++) {
        int ny = y + dy[d], nx = x + dx[d];
        if (!inRange(ny, nx)) continue;
        if (hash[board[ny][nx]]) continue;

        hash[board[ny][nx]] = true;
        ret = max(ret, 1 + dfs(ny, nx));
        hash[board[ny][nx]] = false;
    } 
    return ret;
}

int main() {
    scanf("%d %d", &Y, &X);
    for (int y = 0; y < Y; y++)
        for (int x = 0; x < X; x++)
            scanf(" %c", &board[y][x]);

    hash[board[0][0]] = true;
    printf("%d\n", 1 + dfs(0, 0));
    return 0;
}