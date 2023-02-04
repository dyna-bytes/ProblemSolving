#include <stdio.h>
#define MAXN 16

int N, R;
int A[MAXN];
int ans[MAXN];

struct merge_sort {
    int sorted[MAXN];
    void merge(int A[], int s, int e) {
        int mid = (s + e)/2;
        int l = s, r = mid;
        int i;
        for (i = s; l < mid && r < e; i++)  sorted[i] = (A[l] < A[r]) ? A[l++] : A[r++];
        for (; i < e; i++)                  sorted[i] = (r == e) ? A[l++] : A[r++];
        for (i = s; i < e; i++)             A[i] = sorted[i];
    }
    void sort(int A[], int s, int e) {
        if (s + 1 == e) return;
        int mid = (s + e)/2;
        sort(A, s, mid);
        sort(A, mid, e);
        merge(A, s, e);
    }
};

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
    for (int i = 0; i < N; i++) scanf(" %d", A + i);

    merge_sort MS;
    MS.sort(A, 0, N);
    nPIr();
    return 0;
}