#include <stdio.h>
#define MAXN 20
const int dy[] = { -1, 1, 0, 0 }, dx[] = { 0, 0, -1,1 };
template <class T> const T& max(const T& a, const T& b) {
    return (a > b) ? a : b;
}

#define AND &&
#define OR ||
#define NOT !

int Y, X;
char board[MAXN][MAXN];
int visited[MAXN][MAXN];
int hash;

int dfs(int y, int x) {
    int ret = 0;
    
    // loop unrolling
    if (x + 1 < X AND NOT(hash & (1 << board[y][x + 1]))) {
        hash |= (1 << board[y][x + 1]);
        [&]() {
            if (visited[y][x + 1] == hash) return;
            visited[y][x + 1] = hash;
        
            ret = max(ret, 1 + dfs(y, x + 1));
        } ();
        
        hash &= ~(1 << board[y][x + 1]);
    }    
    if (x > 0 AND NOT(hash & (1 << board[y][x - 1]))) {
        hash |= (1 << board[y][x - 1]);
        [&]() {
            if (visited[y][x - 1] == hash) return;
            visited[y][x - 1] = hash;
        
            ret = max(ret, 1 + dfs(y, x - 1));
        } ();

        hash &= ~(1 << board[y][x - 1]);
    }
    if (y + 1 < Y AND NOT(hash & (1 << board[y + 1][x]))) {
        hash |= (1 << board[y + 1][x]);
        [&]() {
            if (visited[y + 1][x] == hash) return;
            visited[y + 1][x] = hash;

            ret = max(ret, 1 + dfs(y + 1, x));
        } ();

        hash &= ~(1 << board[y + 1][x]);
    }
    if (y > 0 AND NOT(hash & (1 << board[y - 1][x]))) {
        hash |= (1 << board[y - 1][x]);
        [&]() {
            if (visited[y - 1][x] == hash) return;
            visited[y - 1][x] = hash;
            
            ret = max(ret, 1 + dfs(y - 1, x));
        } ();
        
        hash &= ~(1 << board[y - 1][x]);
    }
    
    return ret;
}

int main() {
    scanf("%d %d", &Y, &X);
    for (int y = 0; y < Y; y++)
        for (int x = 0; x < X; x++) {
            scanf(" %c", &board[y][x]);
            board[y][x] -= 'A';
        }

    hash |= (1 << board[0][0]);
    visited[0][0] = hash;
    printf("%d\n", 1 + dfs(0, 0));
    return 0;
}