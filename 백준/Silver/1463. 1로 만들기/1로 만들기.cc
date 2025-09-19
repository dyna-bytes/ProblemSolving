#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define FASTIO cin.tie(0)->sync_with_stdio(0)

#define endl '\n'
#define DEBUG
#ifdef DEBUG
#define debug(x) cout << #x << " is " << x << endl;
#define debugVect(v) do { \
    cout << #v << " is |" ; \
    for (auto i : v) cout << i << "|"; \
    cout << endl; \
} while (0)
#else
#define debug(x)
#define debugVect(v)
#endif

typedef pair<int, int> pii;
const int INF = 1e9;
const int MAXN = 1e6 + 5;

int visited[MAXN];

int bfs(int N) {
    queue<int> q;
    q.push(1);

    int cnt = 0;
    while (!q.empty()) {
        int qsize = q.size();
        for (int i = 0; i < qsize; i++) {
            int n = q.front(); q.pop();
            if (n == N) return cnt;

            if (visited[n]) continue;
            visited[n] = true;
            if (N >= 3*n)
                q.push(3*n);
            if (N >= 2*n)
                q.push(2*n);
            if (N >= n+1)
                q.push(n+1);
            }
        cnt++;
    }
    return -1;
}

int main() {
    FASTIO;
    int N;
    cin >> N;
    cout << bfs(N) << endl;

    return 0;
}