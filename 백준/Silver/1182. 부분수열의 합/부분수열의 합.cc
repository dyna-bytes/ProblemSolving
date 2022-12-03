#include <stdio.h>

int N, S;
int A[21];

int dfs(int n, int s) {
    if (n == N) return 0;

    int ret = (s + A[n] == S);
    ret += dfs(n + 1, s);
    ret += dfs(n + 1, s + A[n]);
    return ret;
}

int main() {
    scanf("%d %d", &N, &S);
    for (int i = 0; i < N; i++)
        scanf("%d", A + i);
    printf("%d", dfs(0, 0));
    return 0;
}