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
const int MOD = 1e9 + 3;

int N, K;
int first_choosed;
vector<vector<vint>> dp;

int f(int n, int k, int prev_choosed) {
    if (n == N) { 
        if (first_choosed) return (!prev_choosed && k == K);
        else return k == K;
    }

    int& ret = dp[n][k][prev_choosed];
    if (ret != -1) return ret;
    
    ret = f(n+1, k, false);
    if (!prev_choosed) (ret += f(n+1, k+1, true)) %= MOD;
    return ret;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> N >> K;

    dp.resize(N+1, vector<vint>(N+1, vint(2, -1)));
    first_choosed = false;
    int ret = f(0, 0, true);

    dp.clear(), dp.resize(N+1, vector<vint>(N+1, vint(2, -1)));
    first_choosed = true;
    (ret += f(1, 1, true)) %= MOD;

    cout << ret;
    return 0;
}