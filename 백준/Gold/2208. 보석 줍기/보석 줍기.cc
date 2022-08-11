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

/**
 * @brief 길이가 M 이상인 부분 배열 중 최대의 합.
 * Maximum Subarray와 똑같은데, min_pSum을 더 느리게 갱신한다.
 * 
 * i >= M 일 때,
 * maxSum(i) := i번째 원소를 포함하며, 길이가 M 이상인 구간 [0, i] 안에서 얻을 수 있는 최대 부분합
 * maxSum(i) = max(0 <= k <= i-M+1){ 구간 [k, i]의 합 }
 *           = max(0 <= k <= i-M+1){ pSum[i+1] - pSum[k] }
 *           = pSum[i+1] - min(0 <= k <= i-M+1){ pSum[i] }
 */
int N, M;
vint pSum;

int solve() {
    int res = 0;
    int min_pSum = 0;
    for (int i = M-1; i < N; i++) {
        // M 칸 전의 pSum을 비로소 현재 비교에 가져오고 min_pSum을 갱신한다.
        min_pSum = min(min_pSum, pSum[i-M+1]);
        res = max(res, pSum[i+1] - min_pSum); 
    }
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> N >> M;
    pSum.resize(N+1);
    for (int i = 0; i < N; i++) {
        int val; cin >> val;
        pSum[i+1] = pSum[i] + val;
    }   
    cout << solve();
    
    return 0;
}