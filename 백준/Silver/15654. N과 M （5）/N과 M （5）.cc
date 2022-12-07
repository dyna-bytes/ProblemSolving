#include <stdio.h>
const int MAXN = 16;
const int INF = 1e9 + 1;

struct merge_sort {
    int* A;
    int tmp[MAXN];
    void sort(int* arr, int arr_size) {
        A = arr;
        divide(0, arr_size);
    }
    void merge(int s, int e) {
        int mid = (s + e)/2;
        int l = s, r = mid;
        int i;
        for (i = s; l < mid && r < e; i++) 
            tmp[i] = (A[l] < A[r]) ? A[l++] : A[r++];
        
        for (; i < e; i++) 
            tmp[i] = (r == e) ? A[l++] : A[r++];
        
        for (int j = s; j < e; j++) 
            A[j] = tmp[j];
    }
    void divide(int s, int e) {
        if (s + 1 == e) return;
        int mid = (s + e)/2;
        divide(s, mid);
        divide(mid, e);
        merge(s, e);
    }
};

int N, R;
int A[MAXN];
int used[MAXN];
int ans[MAXN];

void nPr(int r = 0) {
    if (r == R) {
        for (int i = 0; i < R; i++) printf("%d ", ans[i]);
        printf("\n");
        return;
    }

    for (int i = 0; i < N; i++) {
        if (used[i]) continue;
        used[i] = true;
        ans[r] = A[i];
        nPr(r + 1);

        used[i] = false;
    }
}

int main() {
    scanf("%d %d", &N, &R);
    for (int i = 0; i < N; i++) scanf("%d", A + i);
    merge_sort MS;
    MS.sort(A, N);
    nPr();
    return 0;
}