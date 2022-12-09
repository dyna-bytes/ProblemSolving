#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAXL 9

int N, R;
int A[MAXL];
int sorted[MAXL];
int used[MAXL];
int ans[MAXL];

void nCr(int n = -1, int r = 0) {
    if (r == R) {
        for (int i = 0; i < R; i++) printf("%d ", ans[i]);
        printf("\n");
        return;
    }
    int prev = -1;
    for (int m = n + 1; m < N; m++) {
        if (used[m]) continue;
        if (prev == A[m]) continue;

        used[m] = true;
        prev = ans[r] = A[m];

        nCr(m, r + 1);
        used[m] = false;
    }
}

void merge(int s, int e) {
    int mid = (s + e) / 2;
    int l = s, r = mid;
    int i;
    for (i = s; l < mid && r < e; i++)
        sorted[i] = (A[l] < A[r]) ? A[l++] : A[r++];
    for (; i < e; i++)
        sorted[i] = (r == e) ? A[l++] : A[r++];
    for (i = s; i < e; i++)
        A[i] = sorted[i];
}

void sort(int s, int e) {
    if (s + 1 == e) return;
    int mid = (s + e) / 2;
    sort(s, mid);
    sort(mid, e);
    merge(s, e);
}

int main() {
    scanf("%d %d", &N, &R);
    for (int i = 0; i < N; i++) scanf("%d", A + i);
    sort(0, N);
    nCr();
    return 0;
}