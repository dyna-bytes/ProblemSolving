#if 1
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
//#define DEBUG
#ifdef DEBUG
#include <iostream>
#include <time.h>
using namespace std;
#define FL(f, l) "[" << f << "](" << l << ") "
#define debug(x) cout << FL(__func__, __LINE__) << #x << " is " << x << endl
#define EXPECT_EQ(a, b) do {\
    auto A = a, B = b; \
    if (A != B) cout << FL(__func__, __LINE__) << A << " != " << B << endl; \
} while (0)
#else
#define debug(x) {}
#define EXPECT_EQ(a, b) {}
#endif // DEBUG

const int MAX = 50 + 5;
#define FRONT 0
#define RIGHT 1
#define BACK 2
#define LEFT 3
const int dy[] = { -1, 0, 1, 0 }, dx[] = { 0, 1, 0, -1 };

int Y, X;
int board[MAX][MAX];
bool cleaned[MAX][MAX];
bool inRange(int y, int x) {
    return 0 <= y && y < Y && 0 <= x && x < X;
}
#ifdef DEBUG
void print_map(int Y, int X, int board[MAX][MAX]) {
    for (int y = 0; y < Y; ++y) {
        for (int x = 0; x < X; ++x)
            printf("%d ", board[y][x]);
        printf("\n");
    }
}
#else
void print_map(int Y, int X, int board[MAX][MAX]) {}
#endif // DEBUG

/*
* Logic
* 1. if (!cleaned[y][x]) cleaned[y][x] = true
* 2. if (all_cleaned(y, x))
*       2.1. if (move(y, x, dir, back))
*               goto 1.
*       2.2. else
*               stop
* 3. else
*       3.1. rotate(dir, left)
*            front_y, front_x = get_front(y, x, dir)
*       3.2. if (!cleaned[front_y][front_x])
*               move(y, x, dir, front)
*            goto 1.
*/

void get_next(int y, int x, int dir, int &ny, int &nx, int ndir) {
    ny = y;
    nx = x;
    switch (ndir) {
    case FRONT:
        switch (dir) {
        case FRONT:
            ny--;
            break;
        case BACK:
            ny++;
            break;
        case RIGHT:
            nx++;
            break;
        case LEFT:
            nx--;
            break;
        default:
            break;
        }
        break;
    case BACK:
        switch (dir) {
        case FRONT:
            ny++;
            break;
        case BACK:
            ny--;
            break;
        case RIGHT:
            nx--;
            break;
        case LEFT:
            nx++;
            break;
        default:
            break;
        }
        break;
    default:
        printf("Only FRONT/BACK directions are available\n");
        printf("input next dir: %d\n", ndir);
        break;
    }
}

#ifdef DEBUG
void get_next_test() {
    clock_t time = clock();
    int y = 10, x = 10;
    int ny, nx;
    
    get_next(y, x, FRONT, ny, nx, FRONT);
    EXPECT_EQ(ny, y - 1);
    get_next(y, x, BACK, ny, nx, LEFT);
    EXPECT_EQ(nx, x + 1);
    get_next(y, x, BACK, ny, nx, BACK);
    EXPECT_EQ(ny, y - 1);

    time = clock() - time;
    debug(time);
}
#endif // DEBUG

int move(int& y, int& x, int ny, int nx) {
    if (!inRange(ny, nx)) return false;
    if (board[ny][nx]) return false;
    y = ny, x = nx;
    return true;
}
int move_dir(int& y, int& x, int dir, int ndir) {
    int ny, nx;
    get_next(y, x, dir, ny, nx, ndir);
    return move(y, x, ny, nx);
}

void rotate(int& dir, int ndir) {
    switch (ndir) {
    case FRONT:
        break;
    case RIGHT:
        dir = (dir + 1) % 4;
        break;
    case BACK:
        dir = (dir + 2) % 4;
        break;
    case LEFT:
        dir = (dir + 3) % 4;
        break;
    default:
        break;
    }
}
bool not_cleaned(int y, int x) {
    bool ret = false;
    if (inRange(y - 1, x)) ret |= (!board[y - 1][x] & !cleaned[y - 1][x]);
    if (inRange(y, x + 1)) ret |= (!board[y][x + 1] & !cleaned[y][x + 1]);
    if (inRange(y + 1, x)) ret |= (!board[y + 1][x] & !cleaned[y + 1][x]);
    if (inRange(y, x - 1)) ret |= (!board[y][x - 1] & !cleaned[y][x - 1]);
    return ret;
}
int run(int y, int x, int dir) {
    int cnt = 0;
    while (true) {
        if (!cleaned[y][x]) {
            cleaned[y][x] = true;
            cnt++;
        }
        if (!not_cleaned(y, x)) {
            if (move_dir(y, x, dir, BACK)) continue;
            else break;
        } else {
            rotate(dir, LEFT);
            int ny, nx;
            get_next(y, x, dir, ny, nx, FRONT);
            if (inRange(ny, nx) && !board[ny][nx] && !cleaned[ny][nx])
                move(y, x, ny, nx);
        }
    }
    return cnt;
}

#ifdef DEBUG
int __main() {
#else
int main() {
#endif // DEBUG
    scanf("%d %d\n", &Y, &X);
    int cy, cx, cdir;
    scanf("%d %d %d\n", &cy, &cx, &cdir);

    for (int y = 0; y < Y; ++y) {
        for (int x = 0; x < X; ++x)
            scanf("%d", &board[y][x]);
    }

    print_map(Y, X, board);
    printf("%d\n", run(cy, cx, cdir));
    return 0;
}

#ifdef DEBUG
void main_test() {
    clock_t time = clock();
    memset(cleaned, 0, sizeof(cleaned));
    __main();
    time = clock() - time;
    debug(time);
}
int main() {
    freopen("prob14503_input.txt", "r", stdin);
    get_next_test();
    for (int TC=0; TC<2;++TC)
        main_test();
    return 0;
}
#endif // DEBUG
#endif // 1
