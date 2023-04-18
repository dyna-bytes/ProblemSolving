#include <iostream>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define MAX_SIZE 100000

bool less_than(int x, int y) {
    return x < y;
}

bool greater_or_equal(int x, int y) {
    return x >= y;
}

void merge(int A[], int s, int e, bool (*op)(int, int)=less_than) {
    if (s + 1 == e) return;
    int m = (s + e)/2;
    int l = s, r = m;
    int i, j;
    int sorted[MAX_SIZE];

    for (i = s; l < m && r < e; i++)
        if (op(A[l], A[r])) sorted[i] = A[l++];
        else sorted[i] = A[r++];
    
    j = (r == e) ? l : r;
    for (; i < e; i++)
        sorted[i] = A[j++];

    for (i = s; i < e; i++)
        A[i] = sorted[i];
}

void sort(int A[], int s, int e, bool (*op)(int, int)=less_than) {
    if (s + 1 == e) return;
    int m = (s + e)/2;
    sort(A, s, m, op);
    sort(A, m, e, op);
    merge(A, s, e, op);
}

int greedy(int N, int M, int members[]) {
    sort(members, 0, N);

    int ret = 0;
    for (int l = 0, r = N - 1; l < r; ) {
        if (members[l] + members[r] >= M) {
            l++, r--;
            ret++;
        } else l++;
    }

    return ret;
}

int main() {
    FASTIO;
    
    int N, M;
    cin >> N >> M;

    int members[MAX_SIZE];
    for (int i = 0; i < N; i++)
        cin >> members[i];

    cout << greedy(N, M, members);
    return 0;
}