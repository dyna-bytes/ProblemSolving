#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAXN 8
template <class T> const T& max(const T& a, const T& b) {
    return (a < b) ? b : a; 
}

int N;
int S[MAXN];
int W[MAXN];
int broken[MAXN];

int dfs(int n) {
    auto do_break = [&](int a, int b) {
        S[a] -= W[b];
        S[b] -= W[a];
    };
    auto undo_break = [&](int a, int b) {
        S[a] += W[b];
        S[b] += W[a];
    };

    if (n == N) {
        int cnt = 0;
        for (int i = 0; i < N; i++) cnt += broken[i];
        return cnt;
    }

    int ret = 0;
    bool all_broken = true;
    for (int m = 0; m < N; m++) {
        if (n == m) continue;
        if (broken[n]) continue;
        if (broken[m]) continue;
        all_broken = false;

        do_break(n, m);
        if (S[n] <= 0) broken[n] = true;
        if (S[m] <= 0) broken[m] = true;

        ret = max(ret, dfs(n + 1));

        undo_break(n, m);
        if (S[n] > 0) broken[n] = false;
        if (S[m] > 0) broken[m] = false;
    }
    if (all_broken) ret = max(ret, dfs(n + 1));

    return ret;
}
int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf(" %d %d", &S[i], &W[i]);
    }

    printf("%d\n", dfs(0));
    return 0;
}