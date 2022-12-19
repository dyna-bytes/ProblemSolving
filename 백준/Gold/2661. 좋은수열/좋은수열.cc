#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int N;
int ans[81];

bool isGood(int len) {
    int cnt = 0;
    for (int step = 1; step <= len / 2; step++)
        for (int first = 0; first <= len - step; first++) {
            int count = 0;
            for (int scan = first; scan < first + step && scan + step <= len; scan++)
                if (ans[scan] == ans[scan + step]) count++;

            if (count == step) return false;
        }
    return true;
}

bool dfs(int n) {
    if (n == N) {
        if (!isGood(N)) return false;

        for (int i = 0; i < N; i++) printf("%d", ans[i]);
        return true;
    }

    ans[n] = 1;
    if (ans[n - 1] != 1 && isGood(n) && dfs(n + 1)) return true;
    
    ans[n] = 2;
    if (ans[n - 1] != 2 && isGood(n) && dfs(n + 1)) return true;

    ans[n] = 3;
    if (ans[n - 1] != 3 && isGood(n) && dfs(n + 1)) return true;

    return false;
}

int main() {
    
    scanf("%d", &N);
    dfs(0);
    return 0;
}