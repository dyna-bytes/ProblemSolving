#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define debug(x) cout << "[debug] " << #x << " is " << x << endl
typedef long long ll;
const int MAXN = 3e6 + 1;
const int MAXD = 3e3 + 1;

int N, D, K, C; // 접시 개수, 초밥 종류, 연속 접시, 쿠폰 번호
int sushi[MAXN + MAXD];
int eaten[MAXD];
// 길이가 K인 부분배열에서 고를 수 있는 서로 다른 원소의 최대 개수 + 쿠폰 사용 가능
int solve() {
    int max_eaten = 0;
    int cur_eaten = 0;
    for (int i = 0; i < K; i++) {
        if (eaten[sushi[i]] == 0) cur_eaten++;
        eaten[sushi[i]]++;
    }

    max_eaten = cur_eaten + (eaten[C] == 0);
    for (int i = K; i < N; i++) {
        if (eaten[sushi[i - K]] == 1) cur_eaten--;
        eaten[sushi[i - K]]--;

        if (eaten[sushi[i]] == 0) cur_eaten++;
        eaten[sushi[i]]++;

        max_eaten = max(max_eaten, cur_eaten + (eaten[C] == 0));
    }
    return max_eaten;
}

int main() {
    FASTIO;
    cin >> N >> D >> K >> C;
    for (int i = 0; i < N; i++) cin >> sushi[i];
    for (int i = 0; i < K; i++) sushi[i + N] = sushi[i];
    N += K;
    cout << solve();
    return 0;
}