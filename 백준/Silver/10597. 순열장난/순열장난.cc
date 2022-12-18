#include <stdio.h>
#include <cstring>

template <class T> const T& max (const T& a, const T& b) {
    return (a > b) ? a : b;
}

int N;
char str[501];
int ans[1000];
int used[51];
int s = 0;

bool dfs(int n) {
    if (s > 50) return false;

    if (n == N) {
        int max_num = 0;
        for (int i = 0; i < s; i++) max_num = max(ans[i], max_num);

        for (int num = 1; num <= max_num; num++)
            if (used[num] == false) return false;
            
        for (int i = 0; i < s; i++) printf("%d ", ans[i]);
        return true;
    }

    if (n + 1 < N && str[n + 1] == 0 && str[n] <= 5) {
        if (!used[str[n] * 10]) {
            used[str[n] * 10] = true;
            ans[s++] = str[n] * 10;

            if (dfs(n + 2)) return true;

            used[str[n] * 10] = false;
            s--;
            return false;
        }
    }

    if (n + 1 < N && str[n] <= 4) {
        if (!used[str[n] * 10 + str[n + 1]]) {
            used[str[n] * 10 + str[n + 1]] = true;
            ans[s++] = str[n] * 10 + str[n + 1];

            if (dfs(n + 2)) return true;

            used[str[n] * 10 + str[n + 1]] = false;
            s--;
        }
    }

    if (!used[str[n]] && str[n] >= 0) {
        used[str[n]] = true;
        ans[s++] = str[n];

        if (dfs(n + 1)) return true;

        used[str[n]] = false;
        s--;
    }
    return false;
}
int main() {
    scanf("%s", str);
    N = strlen(str);
    for (int i = 0; i < N; i++)
        str[i] -= '0';
    
    dfs(0);
    return 0;
}