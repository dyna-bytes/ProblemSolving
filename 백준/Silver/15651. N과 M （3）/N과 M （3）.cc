#include <stdio.h>
#define MAXS 8

int N, R;
int A[MAXS];
int used[MAXS];
int ans[MAXS];

// 중복순열(Permutation with repetition)
void nPIr(int r = 0) {
    if (r == R) {
        for (int i = 0; i < R; i++) printf("%d ", ans[i]);
        printf("\n");
        return;
    }

    for (int i = 0; i < N; i++) {
        ans[r] = A[i];
        nPIr(r + 1);
    }
}

int main() {
    scanf("%d %d", &N, &R);
    for (int i = 0; i < N; i++) A[i] = i + 1;
    nPIr();
    return 0;
}