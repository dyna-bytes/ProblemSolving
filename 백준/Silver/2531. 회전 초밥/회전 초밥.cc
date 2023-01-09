#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0)
#define endl '\n'

int N, D, K, coupon;
int sushi[30000 + 1];
int eaten[3000 + 1];
int main() {
    FASTIO;
    cin >> N >> D >> K >> coupon;
    for (int i = 0; i < N; i++) cin >> sushi[i];

    int cnt = 0; // 길이가 K인 구간 내에서 먹은 서로 다른 초밥의 종류
    int max_len = 0;
    int S = 0, E = K;
    for (int i = S; i < E; i++) {
        if (eaten[sushi[i]] == 0) cnt++;
        eaten[sushi[i]]++;
    }

    max_len = cnt + (eaten[coupon] == 0);
    for (int i = 1; i < N; i++) {
        if (--eaten[sushi[S]] == 0) cnt--;
        S = (S + 1) % N;

        if (eaten[sushi[E]]++ == 0) cnt++;
        E = (E + 1) % N;

        max_len = max(max_len, cnt + (eaten[coupon] == 0));
    }

    cout << max_len << endl;
    return 0;
}