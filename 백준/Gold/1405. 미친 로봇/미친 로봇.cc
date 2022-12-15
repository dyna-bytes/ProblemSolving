#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
const int dy[] = { 0, 0, 1, -1 }, dx[] = { -1, 1, 0, 0 };
const int Y = 30, X = 30;

int N; 
double weight[4];
int visited[Y][X];

double ans;

void dfs(int y, int x, double p, int n) {
    if (n == N) {
        ans += p;
        return;
    }

    if (!visited[y][x + 1]) {
        visited[y][x + 1] = true;
        dfs(y, x + 1, weight[0] * p, n + 1);
        visited[y][x + 1] = false;
    }
    if (!visited[y][x - 1]) {
        visited[y][x - 1] = true;
        dfs(y, x - 1, weight[1] * p, n + 1);
        visited[y][x - 1] = false;
    }
    if (!visited[y + 1][x]) {
        visited[y + 1][x] = true;
        dfs(y + 1, x, weight[2] * p, n + 1);
        visited[y + 1][x] = false;
    }
    if (!visited[y - 1][x]) {
        visited[y - 1][x] = true;
        dfs(y - 1, x, weight[3] * p, n + 1);
        visited[y - 1][x] = false;
    }
}

int main() {
    scanf("%d %lf %lf %lf %lf", &N, &weight[0], &weight[1], &weight[2], &weight[3]);
    weight[0] /= 100; weight[1] /= 100; weight[2] /= 100; weight[3] /= 100;
    visited[15][15] = true;
    dfs(15, 15, 1.0, 0);
    printf("%.9f\n", ans);
    return 0;
}