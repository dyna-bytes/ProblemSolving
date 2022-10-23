#include <bits/stdc++.h>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define debugVec(v) do { \
    std::cout << "[Debug] ["; \
    for(int i = 0; i < ((v.size())-1); i++) std::cout << v[i] << "|"; \
    std::cout << v[((v.size())-1)] << "]\n"; \
} while(0)
#define debugV2D(v) do { \
    std::cout << "[Debug] [\n"; \
    for(int y = 0; y < (v.size()); y++) { \
        if(v[y].empty()){ std::cout << "  []\n"; continue; } \
        std::cout << "  ["; \
        for(int x = 0; x < ((v[y].size())-1); x++) \
            std::cout << v[y][x] << "|"; \
        std::cout << v[y][(v[y].size())-1] << "]\n"; \
    } \
    std::cout << "]\n"; \
} while(0)
#define endl '\n'
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vint;
typedef vector<pii> vpii;

#define mStartDay first
#define mEndDay second

int convert_month_day(int month, int day) {
    return month * 100 + day;
}

/**
 * @brief Two Pointer, Greedy
 * 꽃이 03월 01일부터 11월 30일 까지 끊임없이 계속 피어있으려면
 * 결국 모든 꽃의 구간을 겹쳤을 때, 하나의 "연속된 구간"이 나와야 한다.
 * 따라서, 현재까지 만들 수 있는 최대의 구간 내에서 
 * 가장 오른쪽으로 갈 수 있는 새로운 구간의 상한을 찾고
 * 이를 다시 현재 구간의 상한으로 삼아 다시 하나의 연속된 구간을 만들어내면 된다.
 * (이 구간은 과거부터 연속된 하나의 구간이며, 현재까지 만들 수 있는 최대 길이의 구간이다.)
 */
int solve(int N, vpii& flowers) {
    unordered_map<int, int> endDays;
    for (pii flower: flowers) // largest endDay of each startDay
        endDays[flower.mStartDay] = max(endDays[flower.mStartDay], flower.mEndDay);
    
    int ret = 0;
    int s = convert_month_day(01, 01);
    int e = convert_month_day(03, 01);

    // 구간의 우측 끝이 11월 30일을 넘는다면 종료
    while (e <= convert_month_day(11, 30)) {
        int max_e = 0;

        // 구간 [s, e]에서 가장 지는 날이 늦는 꽃을 찾음
        for (; s <= e; s++)
            max_e = max(max_e, endDays[s]);

        // 더 이상 우향하는 연속되는 구간을 만들어내지 못할 경우
        if (max_e < e) return 0;
        // 구간의 우측 끝 갱신
        e = max_e;
        ret++;
    }

    return ret;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int N; cin >> N;
    vpii flowers(N);
    for (int i = 0; i < N; i++) {
        int s_m, s_d, e_m, e_d;
        cin >> s_m >> s_d >> e_m >> e_d;
        flowers[i] = {convert_month_day(s_m, s_d), convert_month_day(e_m, e_d)};
    }
    
    cout << solve(N, flowers);
    return 0;
}