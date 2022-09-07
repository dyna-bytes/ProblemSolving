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
const int INF = 1e9 + 1;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N, M;
    cin >> N >> M;

    int total_cost = 0;
    vint mems(N+1), costs(N+1);
    for (int i = 0; i < N; i++) cin >> mems[i];
    for (int i = 0; i < N; i++){ 
        cin >> costs[i];
        total_cost += costs[i];
    }

    vint dp(total_cost + 1); // dp[c]: 비용 c로 만들 수 있는 최대 메모리
    // dp[i][c] = max(c){ dp[i-1][c-costs] } + mems[i]
    // 이전의 앱들로 (c-costs)의 비용을 들여 만든 최대 메모리 
    // + 만드는 데 (costs)의 비용이 드는 현재 앱의 메모리
    // c: 현재 앱의 비용 이상으로 가능한 모든 비용. 즉, [현재 앱의 비용, 전체 앱의 비용]
    
    for (int i = 0; i < N; i++)
        for (int c = total_cost; c >= costs[i]; c--) // 뒤에서부터 내려와야 mems[i]가 중복으로 더해지지 않음
            dp[c] = max(dp[c], dp[c - costs[i]] + mems[i]);
            // 이전 단계에서 계산된 dp값과 현재 단계의 mems값을 더해야하므로
            // dp[c-costs[i]]는 i-1 단계의 dp값, mems[i]는 i 단계의 메모리 값임.
    
    for (int c = 0; c <= total_cost; c++)
        if (dp[c] >= M) {
            cout << c;
            break;
        }
    
    return 0;
}