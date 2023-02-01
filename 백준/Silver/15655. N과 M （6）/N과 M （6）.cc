#include <stdio.h>
const int MAXN = 16;
const int INF = 1e9;

int N, R;
int A[MAXN];
int sorted[MAXN];
int used[MAXN];
int ans[MAXN];

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
        nCr(m, r + 1);

        used[m] = false;
    }
}
void merge(int s, int e) {
    int mid = (s + e)/2;
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
    int mid = (s + e)/2;
    sort(s, mid);
    sort(mid, e);
    merge(s, e);
}

int main() {
    scanf("%d %d", &N, &R);
    for (int i = 0; i < N; i++) scanf(" %d", A + i);

    sort(0, N);
    nCr();
    return 0;
}