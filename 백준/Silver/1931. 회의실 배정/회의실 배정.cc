#if 1
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#ifndef BOJ
#include <iostream>
#include <time.h>
#include <cstdarg>
using namespace std;
#define FL "[" << __func__ << "](" << __LINE__ << ") "
#define debug(x) cout << FL << #x << " is " << x << endl;
#define EXPECT_EQ(a, b) do {\
    auto A = a, B = b; \
    if (A != B) cout << FL << A << " != " << B << endl; \
} while (0)
#else
#define debug(x)
#define EXPTEC_EQ(a, b)
#endif // !BOJ
void dprintf(const char* __format, ...) {
#ifndef BOJ
    va_list args;
    va_start(args, __format);
    printf("[DEBUG] ");
    vprintf(__format, args);
    va_end(args);
#endif // !BOJ
}

typedef long long ll;
typedef struct Pair {
    ll first, second;
    Pair() {
        first = 0, second = 0;
    };
    Pair(ll _f, ll _s) {
        first = _f, second = _s;
    }
    // 끝나는 시간이 가장 빠른 순으로 정렬
    bool operator < (Pair &other) {
        if (second == other.second) return first < other.first;
        return second < other.second;
    }
} Pair;

const int MAX = 100'000 + 5;
int N;
Pair meetings[MAX];
Pair sorted[MAX];
void merge(int s, int e) {
    if (s + 1 == e) return;
    int m = (s + e) / 2;
    int l, r, i;
    for (l = s, r = m, i = s; l < m && r < e; ) {
        if (meetings[l] < meetings[r]) {
            sorted[i] = meetings[l];
            l++, i++;
        } else {
            sorted[i] = meetings[r];
            r++, i++;
        }
    }

    for (int j = (l == m) ? r : l; i < e; ) {
        sorted[i] = meetings[j];
        j++, i++;
    }

    for (i = s; i < e; i++)
        meetings[i] = sorted[i];
}
// sort [s, e)
void sort(int s, int e) {
    if (s + 1 == e) return;
    int m = (s + e) / 2;
    sort(s, m);
    sort(m, e);
    merge(s, e);
}

int solve() {
    ll e = 0;
    int cnt = 0;

    for (int i = 0; i < N; ++i) {
        if (e <= meetings[i].first) {
            e = meetings[i].second;
            cnt++;
        }
    }
    return cnt;
}

#ifndef BOJ
int __main() {
#else
int main() {
#endif // !BOJ
    scanf("%d\n", &N);
    ll s, e;
    for (int i = 0; i < N; ++i) {
        scanf("%lld %lld\n", &s, &e);
        meetings[i] = Pair(s, e);
    }
    sort(0, N);

    for (int i = 0; i < N; ++i) 
        dprintf("[%d %d]\n", meetings[i].first, meetings[i].second);
    
    printf("%d\n", solve());
    return 0;
}

#ifndef BOJ
void main_test() {
    clock_t time = clock();
    __main();
    time = clock() - time;
    debug(time);
}
int main() {
    freopen("prob1931_input.txt", "r", stdin);
    main_test();
    return 0;
}
#endif // !BOJ
#endif