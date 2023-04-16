#include <iostream>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define MAX_SIZE 50
void merge(int s, int e, int A[], bool increasing = true) {
    int m = (s + e) / 2;
    
    int sorted[MAX_SIZE];
    int i, l = s, r = m;
    for (i = s; l < m && r < e; i++)
        if ((A[l] > A[r]) ^ increasing) sorted[i] = A[l++];
        else sorted[i] = A[r++];

    int residual = (r == e) ? l : r;
    for (; i < e; i++)
        sorted[i] = A[residual++];

    for (i = s; i < e; i++)
        A[i] = sorted[i];
}

void sort(int s, int e, int A[], bool increasing = true) {
    if (s + 1 == e) return;
    int m = (s + e) / 2;
    
    sort(s, m, A, increasing);
    sort(m, e, A, increasing);
    merge(s, e, A, increasing);
}

int N;
int A[MAX_SIZE];
int B[MAX_SIZE];
void input() {
    cin >> N;
    for (int i = 0; i < N; i++) cin >> A[i];
    for (int i = 0; i < N; i++) cin >> B[i];
}

int greedy() {
    sort(0, N, A);
    sort(0, N, B, false);

    int ret = 0;
    for (int i = 0; i < N; i++)
        ret += A[i] * B[i];
    return ret;
}

int main() {
    FASTIO;
    input();
    cout << greedy();
    return 0;
}