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
#define Y first
#define X second

int N, W;
vpii works;
vector<vint> dp;

int dist(pii p1, pii p2) {
    return abs(p1.Y - p2.Y) + abs(p1.X - p2.X);
}

// dp[p1][p2] : 경찰차1이 마지막으로 해결한 사건이 p1 - 1,
// 경찰차2가 마지막으로 해결한 사건이 p2 - 1 일 때,
// max(p1, p2) ~ W 까지의 최단 거리 합(현재 해결해야 할 일부터 마지막 일까지)
// Let curr_work = max(p1, p2), next_work = curr_work + 1
// dp[p1][p2] = min( dist(W[p1-1], W[curr_work]) + dp[next_work][p2],
//                   dist(W[p2-1], W[curr_work]) + dp[p1][next_work] )

int f(int police1, int police2) { // p1: 경찰차1의 다음 목표, p2: 경찰차2의 다음 목표
    if (police1 == W || police2 == W) return 0;

    int& ret = dp[police1][police2];
    if (ret != -1) return ret;

    ret = INT_MAX;
    int curr_work = max(police1, police2); // 현재 해결해야하는 일
    
    // 경찰차1이 현재 일을 해결하러 가는데 드는 비용
    int work_police1 = (police1 == 0 ?
    dist({1, 1}, works[curr_work]) : dist(works[police1 - 1], works[curr_work]));

    // 경찰차2가 현재 일을 해결하러 가는데 드는 비용
    int work_police2 = (police2 == 0 ?
    dist({N, N}, works[curr_work]) : dist(works[police2 - 1], works[curr_work]));

    ret = min(work_police1 + f(curr_work + 1, police2),
                work_police2 + f(police1, curr_work + 1));
    return ret;
}

void tracking(int police1, int police2) {
    if (police1 == W || police2 == W) return;

    int curr_work = max(police1, police2);
    // 경찰차1이 현재 일을 해결하러 가는데 드는 비용
    int work_police1 = (police1 == 0 ?
    dist({1, 1}, works[curr_work]) : dist(works[police1 - 1], works[curr_work]));

    // 경찰차2가 현재 일을 해결하러 가는데 드는 비용
    int work_police2 = (police2 == 0 ?
    dist({N, N}, works[curr_work]) : dist(works[police2 - 1], works[curr_work]));

    if (work_police1 + f(curr_work + 1, police2) < work_police2 + f(police1, curr_work + 1)) {
        cout << 1 << endl;
        tracking(curr_work + 1, police2);
    } else {
        cout << 2 << endl;
        tracking(police1, curr_work + 1);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> N;
    cin >> W;
    works.resize(W+2);
    dp.resize(W+1, vint(W+1, -1));
    for (int i = 0; i < W; i++) cin >> works[i].Y >> works[i].X;
    
    cout << f(0, 0) << endl;
    tracking(0, 0);

    return 0;
}