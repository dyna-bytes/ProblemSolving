#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
typedef long long ll;
const int MAXN = 1e5 + 1;

ll N, M;
ll A[MAXN];
ll psum[MAXN];

int main() {
    FASTIO;
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        psum[i + 1] = psum[i] + A[i];
    }

    int s, e;
    for (int i = 0; i < M; i++) {
        cin >> s >> e;
        cout << psum[e] - psum[s - 1] << endl;
    }

    return 0;
}