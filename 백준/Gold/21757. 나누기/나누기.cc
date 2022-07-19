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
        std::cout << "  ["; \
        for(int x = 0; x < ((v[y].size())-1); x++) \
            std::cout << v[y][x] << "|"; \
        std::cout << v[y][(v[y].size())-1] << "]\n"; \
    } \
    std::cout << "]\n"; \
} while(0)
#define endl '\n'
typedef long long ll;
typedef pair<int, int> P;

int N;
ll division;
vector<ll> prefix_sum;
vector<vector<ll>> dp;

// 현재 idx까지 cnt개의 빗금을 쳤을 때, 4개의 분할을 만들 수 있는 경우의 수
ll f(int idx, int cnt) {
    ll& ret = dp[idx][cnt];
    if (ret != -1) return ret;
    if (idx == N) return ret = 0;
    if (cnt == 3) { // 3개의 빗금을 쳤을 때
        if (idx < N) return ret = 1; // 유효한 분할 영역인 경우
        else return ret = 0; // idx >= N 이면 3번째 빗금을 쳐도 의미가 없음.
    }
    
    ret = 0;
    // 현재 인덱스에서 분할을 시도하거나
    if (prefix_sum[idx] == (cnt + 1)*division) 
        ret = f(idx+1, cnt+1);
    // 시도하지 않거나
    ret += f(idx+1, cnt);
    return ret;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> N;
    prefix_sum.resize(N); // zero base index
    dp.resize(N+1, vector<ll>(4, -1));

    cin >> prefix_sum[0];
    for (int i = 1; i < N; i++) {
        ll inp; cin >> inp;
        prefix_sum[i] = prefix_sum[i-1] + inp;
    }

    if (prefix_sum[N-1] % 4) {
        cout << 0;
        return 0;
    }

    division = prefix_sum[N-1] / 4;

    cout << f(0, 0);
    return 0;
}