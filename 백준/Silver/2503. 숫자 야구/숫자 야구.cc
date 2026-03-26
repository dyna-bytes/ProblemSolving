#include <stdio.h>

const int MAXSIZE = 1000;
const int MAXN = 100;
typedef struct {
    int s[MAXSIZE];
    int sz = 0;
    void push(int val) {
        s[sz++] = val;
    }
    int pop() {
        return s[--sz];
    }
    int top() {
        return s[sz - 1];
    }
    int size() {
        return sz;
    }
} stack;

void query(int ans, int num, int& strike, int& ball) {
    strike = 0, ball = 0;
    int a2 = ans / 100;
    int a1 = (ans / 10) % 10;
    int a0 = ans % 10;

    int b2 = num / 100;
    int b1 = (num / 10) % 10;
    int b0 = num % 10;

    if (a2 == b2) strike++;
    else if (a2 == b1 || a2 == b0) ball++;

    if (a1 == b1) strike++;
    else if (a1 == b2 || a1 == b0) ball++;

    if (a0 == b0) strike++;
    else if (a0 == b2 || a0 == b1) ball++;
}

int solve(int N, int nums[MAXN], int strikes[MAXN], int balls[MAXN]) {
    stack st;
    for (int n = 111; n <= 999; n++) {
        int n2 = n / 100;
        int n1 = (n / 10) % 10;
        int n0 = n % 10;
        if (n2 == n1 || n1 == n0 || n2 == n0) continue;
        if (n2 == 0 || n1 == 0 || n0 == 0) continue;
        st.push(n);
    }

    for (int i = 0; i < N; i++) {
        stack buf;
        while (st.size()) {
            int candi = st.pop();
            int strike, ball;
            query(candi, nums[i], strike, ball);
            if (strike == strikes[i] && ball == balls[i])
                buf.push(candi);
        }
        st = buf;
    }

    return st.size();
}

int main() {
    int N;
    scanf("%d", &N);

    int nums[MAXN];
    int strikes[MAXN];
    int balls[MAXN];

    for (int i = 0; i < N; i++)
        scanf("%d %d %d", &nums[i], &strikes[i], &balls[i]);

    printf("%d", solve(N, nums, strikes, balls));

    return 0;
}