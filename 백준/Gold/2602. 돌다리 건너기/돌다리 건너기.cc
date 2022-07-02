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

int N, K;
string rule;
string upper, lower;
vector<vector<int>> dp;

// f: 현재 rule[k]가 upper[n] 혹은 lower[n]에 있는지 찾는 함수
int f(int k, int n, bool isUpper){ // k: rule[], n: upper[] or lower[]
    int& ret = dp[k][n];
    if (ret != -1) return ret;

    if (k == K) return ret = 1;
    if (n == N) {
        if (k == K) return ret = 1;
        else return ret = 0;
    }

    ret = 0;
    if (isUpper) {
        for (; n < N; n++) {
            if (upper[n] == rule[k]) {
                ret += f(k+1, n+1, false);
            }
        }
    } else {
        for (; n < N; n++) {
            if (lower[n] == rule[k]) {
                ret += f(k+1, n+1, true);
            }
        }
    }
    return ret;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> rule;
    cin >> upper;
    cin >> lower;

    K = rule.size();
    N = upper.size();

    dp.resize(K+1, vector<int>(N+1, -1));
    int ans = f(0, 0, true);

    dp.clear();
    dp.resize(K+1, vector<int>(N+1, -1));
    ans += f(0, 0, false);

    cout << ans;
    
    return 0;
}