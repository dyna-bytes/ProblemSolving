#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAXN 15

int N;
int x_map[MAXN];
int left_offset_map[MAXN * 2 + 1]; // lom[b + MAXN] = true, where y = x + b
int right_offset_map[MAXN * 2 + 1]; // rom[b] = true, where y = -x + b

int get_left_offset(int y, int x) {
    return (y - x) + MAXN; // b = (y - x)
}

int get_right_offset(int y, int x) {
    return (y + x);
}

int dfs(int y) {
    if (y == N) return 1;

    int ret = 0;
    int left_offset, right_offset;
    for (int nx = 0; nx < N; nx++) {
        if (x_map[nx]) continue;
        if (left_offset_map[left_offset = get_left_offset(y, nx)]) continue;
        if (right_offset_map[right_offset = get_right_offset(y, nx)]) continue;

        x_map[nx] = true;
        left_offset_map[left_offset] = true;
        right_offset_map[right_offset] = true;
        ret += dfs(y + 1);

        x_map[nx] = false;
        left_offset_map[left_offset] = false;
        right_offset_map[right_offset] = false;
    }
    return ret;
}

int main() {
    scanf("%d", &N);

    printf("%d\n", dfs(0));
    return 0;
}