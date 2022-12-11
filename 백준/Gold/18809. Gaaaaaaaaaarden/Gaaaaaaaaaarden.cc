#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#define MAX(a, b) (((a)>(b))?(a):(b))
#define MAXN 50
#define WATER 0
#define NOT_AVAIL 1
#define AVAILABLE 2
#define RED 3
#define GREEN 4

const int dy[] = {-1, 1, 0, 0}, dx[] = {0, 0, -1, 1};

int Y, X;
int G, R;
int board[MAXN][MAXN];
int visited[MAXN][MAXN];
int red_visited[MAXN][MAXN];
bool inRange(int y, int x) { return 0 <= y && y < Y && 0 <= x && x < X; }

int q_now = 0;
int q_last = 0;
int q_y_x[10000];
int q_depth[10000];
int q_is_red[10000];
int bfs() {
    int flowers = 0;
    while(q_now < q_last) {
        int y = q_y_x[q_now] / X, x = q_y_x[q_now] % X;
        int depth = q_depth[q_now];
        int is_red = q_is_red[q_now];
        q_now++;
        
        if (red_visited[y][x] == 10) continue;

        for (int d = 0; d < 4; d++) {
            int ny = y + dy[d], nx = x + dx[d];
            if (!inRange(ny, nx)) continue;
            if (board[ny][nx] == WATER) continue;
            if (visited[ny][nx]) {
                if (visited[ny][nx] == depth + 1 && red_visited[ny][nx] + is_red == RED + GREEN) {
                    flowers++;
                    red_visited[ny][nx] = 10;
                }
                continue; 
            }

            visited[ny][nx] = depth + 1;
            red_visited[ny][nx] = is_red;
            q_y_x[q_last] = ny * X + nx;
            q_depth[q_last] = depth + 1;
            q_is_red[q_last] = is_red;
            q_last++;
        }
    }
    // printf("flowers: %d\n", flowers);
    return flowers;
}

int supplements[MAXN * MAXN]; // y_x
int reds[MAXN * MAXN];
int greens[MAXN * MAXN];

void init() {
    q_now = q_last = 0;
    memset(visited, 0, sizeof(visited));
    memset(red_visited, 0, sizeof(red_visited));

    for (int i = 0; i < R; i++) {
        q_y_x[q_last] = reds[i];
        q_depth[q_last] = 1;
        q_is_red[q_last] = RED;
        q_last++;
        
        int y = reds[i] / X, x = reds[i] % X;
        visited[y][x] = 1;
        red_visited[y][x] = RED;
    }        
    
    for (int i = 0; i < G; i++) {
        q_y_x[q_last] = greens[i];
        q_depth[q_last] = 1;
        q_is_red[q_last] = GREEN;
        q_last++;

        int y = greens[i] / X, x = greens[i] % X;
        visited[y][x] = 1;
        red_visited[y][x] = GREEN;
    }       
}

int N;
int r = 0, g = 0;
int ans = 0;
void dfs(int n, int red, int green) {
    if (red == 0 && green == 0) {
        init();

        int ret = bfs(); 
        if (ans < ret)
            ans = ret;
        return;
    }

    for (int m = n; m < N; m++) {
        if (red > 0) {
            reds[r++] = supplements[m];
            dfs(m + 1, red - 1, green);
            r--;
        }
        if (green > 0) {
            greens[g++] = supplements[m];
            dfs(m + 1, red, green - 1);
            g--;
        }
    }
}

int main() {
    scanf("%d %d %d %d", &Y, &X, &G, &R);
    N = 0;
    for (int y = 0; y < Y; y++)
        for (int x = 0; x < X; x++) {
            scanf(" %d", &board[y][x]);

            if (board[y][x] == AVAILABLE)
                supplements[N++] = y * X + x;
        }

    dfs(0, R, G);
    printf("%d\n", ans);
    return 0;
}