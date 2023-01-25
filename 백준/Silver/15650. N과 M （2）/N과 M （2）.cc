#include <stdio.h>
#define MAXS 9

int N, R;
int A[MAXS];
int used[MAXS];
int ans[MAXS];

void nCr(int n = -1, int r = 0) {
    if (r == R) {
        for (int i = 0; i < R; i++) printf("%d ", ans[i]);
        printf("\n");
        return;
    }

    for (int m = n + 1; m < N; m++) {
        if (used[m]) continue;
        used[m] = true;
        ans[r] = A[m];
        nCr(m, r+1);

        used[m] = false;
    }
}

int main() {
    scanf("%d %d", &N, &R);
    for (int i = 0; i < N; i++) A[i] = i + 1;
    nCr();
    return 0;
}