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

int N;
vector<vint> costs;
vector<vint> dp;

int first_color;
int f(int n, int prev_color) {
    if (n == N) return (prev_color == first_color) ? INF : 0;
    
    int& ret = dp[n][prev_color];
    if (ret != -1) return ret;

    ret = INF;
    for (int curr_color = 0; curr_color < 3; curr_color++) {
        if (curr_color == prev_color) continue;
        ret = min(ret, costs[n][curr_color] + f(n+1, curr_color));
    }
    return ret;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> N;
    costs.resize(N, vint(3));
    dp.resize(N+1, vint(3, -1));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < 3; j++)
            cin >> costs[i][j];
    
    int ret = INF;
    for (first_color = 0; first_color < 3; first_color++) {
        dp.clear(), dp.resize(N+1, vint(3, -1));
        ret = min(ret, costs[0][first_color] + f(1, first_color));
    }
    cout << ret;
    
    return 0;
}