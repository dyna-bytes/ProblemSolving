#include <stdio.h>
#define MAXS 9

int N, R;
int A[MAXS];
int ans[MAXS];

// 중복조합(Combination with repetition)
void nHr(int n = 0, int r = 0) {
    if (r == R) {
        for (int i = 0; i < R; i++) printf("%d ", ans[i]);
        printf("\n");
        return;
    }

    for (int m = n; m < N; m++) {
        ans[r] = A[m];
        nHr(m, r + 1);
    }
}

int main() {
    scanf("%d %d", &N, &R);
    for (int i = 0; i < N; i++) A[i] = i + 1;
    nHr();
    return 0;
}