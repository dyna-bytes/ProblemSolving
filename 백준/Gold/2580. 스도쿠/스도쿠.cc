#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

const int N = 9;

int board[N][N];
int y_map[N][N + 1]; // map[y][num] = true
int x_map[N][N + 1]; // map[x][num] = true 
int z_map[N][N + 1]; // map[z][num] = true, z = (y/3)*3 + x/3

bool dfs(int y_x) {
    if (y_x == N * N) {
        for (int y = 0; y < N; y++) {
            for (int x = 0; x < N; x++) printf("%d ", board[y][x]);
            printf("\n");
        }
        return true;
    }

    int y = y_x / N;
    int x = y_x % N;
    if (board[y][x]) return dfs(y_x + 1);
    for (int n = 1; n <= N; n++) {
        if (y_map[y][n]) continue;
        if (x_map[x][n]) continue;
        if (z_map[(y / 3) * 3 + x / 3][n]) continue;

        y_map[y][n] = x_map[x][n] = z_map[(y / 3) * 3 + x / 3][n] = true;
        board[y][x] = n;

        if (dfs(y_x + 1)) return true;

        y_map[y][n] = x_map[x][n] = z_map[(y / 3) * 3 + x / 3][n] = false;
        board[y][x] = 0;
    }
    return false;
}

int main() {
    for (int y = 0; y < N; y++) 
        for (int x = 0; x < N; x++) {
            scanf(" %d", &board[y][x]);
            if (board[y][x]) {
                y_map[y][board[y][x]] = true;
                x_map[x][board[y][x]] = true;
                z_map[(y / 3) * 3 + x / 3][board[y][x]] = true;
            }
        }
    dfs(0);
    return 0;
}