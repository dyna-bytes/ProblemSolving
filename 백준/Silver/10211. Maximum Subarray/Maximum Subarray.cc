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
const int INF = 1e9;

/**
 * @brief dp + prefix sum / Kadane's algorithm
 * 길이가 M 이상인 부분배열 중 최대 부분합을 구하라.
 * 
 * [카데인 알고리즘]
 * subproblem 관계: 현재 최대 부분합이 이전 최대 부분합을 포함한다.
 * 
 * 선택지: 직전 인덱스가 갖고 있는 누적합을 연장해보고,
 * 이전까지의 최소 누적합과의 차이를 통해 연속 최대 부분합을 갱신한다.
 * 
 * 점화식:
 * maxSum(i) := i번째 원소를 포함하며, 구간 [0, i] 안에서 얻을 수 있는 최대 부분합
 * maxSum(i) = max(0 <= k <= i){ 구간 [k, i]의 합 }
 *           = max(0 <= k <= i){ pSum(i+1) - pSum(k) }
 *           = pSum(i+1) - min(0 <= k <= i){ pSum(k) } // pSum(i+1)은 k와 아무 상관이 없으므로
 * 한편, 
 * i < j일 때, min(0 <= k <= i){ pSum(k) } >= min(0 <= k <= j){ pSum(k) }
 * // 부분합에 포함할 후보가 늘어나면 최소 부분합은 작아질 수는 있어도 커질 수는 없다.
 */
int N, M;
vint X(1000);

void solve() {
    int N; cin >> N;
    X.clear(); X.resize(N);
    for (int i = 0; i < N; i++) cin >> X[i];

    int curr_pSum = 0; // 구간 [0, i]의 합
    int min_pSum = 0; // k <= i일 때, 구간 [0, k]의 합들 중 최솟값
    int res = -INF;
    for (int i = 0; i < N; i++) {
        curr_pSum += X[i];
        res = max(res, curr_pSum - min_pSum);
        min_pSum = min(curr_pSum, min_pSum);
    }
    cout << res << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int T; cin >> T;
    while (T--) solve();
    return 0;
}