#include <stdio.h>
#define MAXN 9
const int INF = 1e9;

int N, R;
int A[MAXN];
int sorted[MAXN];
int used[MAXN];
int ans[MAXN];

void merge(int s, int e) {
    int mid = (s + e)/2;
    int l = s, r = mid;
    int i;
    for (i = s; l < mid && r < e; i++) {
        if (A[l] < A[r]) 
            sorted[i] = A[l++];
        else 
            sorted[i] = A[r++];
    }
    for (; i < e; i++)
        sorted[i] = (r == e) ? A[l++] : A[r++];
    for (i = s; i < e; i++)
        A[i] = sorted[i];
}

void sort(int s, int e) {
    if (s + 1 == e) return;
    int mid = (s + e)/2;
    sort(s, mid);
    sort(mid, e);
    merge(s, e);
}

void nPr(int r = 0) {
    if (r == R) {
        for (int i = 0; i < R; i++) printf("%d ", ans[i]);
        printf("\n");
        return;
    }

    int prev = -1;
    for (int i = 0; i < N; i++) {
        if (used[i]) continue;
        if (prev == A[i]) continue;

        used[i] = true;
        prev = ans[r] = A[i];
        nPr(r + 1);

        used[i] = false;
    }
}
int main() {
    scanf("%d %d", &N, &R);
    for (int i = 0; i < N; i++) scanf(" %d", A + i);
    sort(0, N);

    nPr();
    return 0;
}