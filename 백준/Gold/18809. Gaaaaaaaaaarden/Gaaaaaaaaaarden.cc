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
#define FLOWER 5

const int dy[] = {-1, 1, 0, 0}, dx[] = {0, 0, -1, 1};

int Y, X;
int G, R;
int board[MAXN][MAXN];
int visited[MAXN][MAXN];
int status[MAXN][MAXN];
inline bool inRange(int y, int x) { return 0 <= y && y < Y && 0 <= x && x < X; }

int q_now = 0;
int q_last = 0;
int q_y_x[10000];

int bfs() {
    int flowers = 0;
    while(q_now < q_last) {
        int y = q_y_x[q_now] / X, x = q_y_x[q_now] % X;
        q_now++;

        int depth = visited[y][x];
        int is_red = status[y][x];
        
        if (status[y][x] == FLOWER) continue;

        for (int d = 0; d < 4; d++) {
            int ny = y + dy[d], nx = x + dx[d];
            if (!inRange(ny, nx)) continue;
            if (board[ny][nx] == WATER) continue;
            if (visited[ny][nx]) {
                if (visited[ny][nx] == depth + 1 && status[ny][nx] + is_red == RED + GREEN) {
                    flowers++;
                    status[ny][nx] = FLOWER;
                }
                continue; 
            }

            visited[ny][nx] = depth + 1;
            status[ny][nx] = is_red;
            q_y_x[q_last] = ny * X + nx;
            q_last++;
        }
    }

    return flowers;
}

int supplements[MAXN * MAXN]; // y_x
int reds[MAXN * MAXN];
int greens[MAXN * MAXN];

void init() {
    q_now = q_last = 0;
    memset(visited, 0, sizeof(visited));
    memset(status, 0, sizeof(status));

    for (int i = 0; i < R; i++) {
        q_y_x[q_last] = reds[i];
        q_last++;
        
        int y = reds[i] / X, x = reds[i] % X;
        visited[y][x] = 1;
        status[y][x] = RED;
    }        
    
    for (int i = 0; i < G; i++) {
        q_y_x[q_last] = greens[i];
        q_last++;

        int y = greens[i] / X, x = greens[i] % X;
        visited[y][x] = 1;
        status[y][x] = GREEN;
    }       
}

int N;
int r = 0, g = 0;
int ans = 0;
void dfs(int n) {
    if (r == R && g == G) {
        init();
        int ret = bfs(); 
        ans = MAX(ans, ret);
        return;
    }

    for (register int m = n + 1; m < N; m++) {
        if (r < R) {
            reds[r++] = supplements[m];
            dfs(m);
            r--;
        }
        if (g < G) {
            greens[g++] = supplements[m];
            dfs(m);
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

    dfs(-1);
    printf("%d\n", ans);
    return 0;
}