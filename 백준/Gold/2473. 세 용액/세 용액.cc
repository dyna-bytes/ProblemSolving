#include <bits/stdc++.h>
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef long long ll;
#define ABS(x) (((x) < 0) ? -(x) : (x)) 
ll A[5001];
ll sorted[5001];
void merge(int s, int e) {
    int mid = (s + e) / 2;
    int l = s;
    int r = mid;
    int i;
    for (i = s; l < mid && r < e; i++) sorted[i] = (A[l] < A[r]) ? A[l++] : A[r++];
    for (; i < e; i++) sorted[i] = (r == e) ? A[l++] : A[r++];
    for (i = s; i < e; i++) A[i] = sorted[i];
}

void sort(int s, int e) {
    if (s + 1 == e) return;
    int mid = (s + e) / 2;
    sort(s, mid);
    sort(mid, e);
    merge(s, e);
}

int main() {
    int N; cin >> N;
    for (int i = 0; i < N; i++) cin >> A[i];
    sort(0, N);
    
    ll sum = 1e9 * 3 + 1;
    ll S, L, R;
    for (int i = 0; i < N - 2; i++) {
        for (int s = i + 1, e = N - 1; s < e; ) {
            if (ABS(sum) > ABS(A[s] + A[e] + A[i])) {
                sum = A[s] + A[e] + A[i];
                S = A[i], L = A[s], R = A[e];
            }
            if (A[s] + A[e] + A[i] < 0) s++;
            else e--;
        }
    }
    cout << S << " " << L << " " << R << endl;
    return 0;
}