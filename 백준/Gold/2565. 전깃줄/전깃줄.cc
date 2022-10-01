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

const int SIZE_N = 501;
vint A(SIZE_N);
vint dp(SIZE_N);

int f(int curr) {
    if (curr == SIZE_N) return dp[curr] = 0;

    int max_dp = 0;
    int max_next = 0;
    for (int next = curr + 1; next < SIZE_N; next++) {
        if (A[next] > A[curr] && A[curr] > 0)
            if (max_dp < dp[next]) {
                max_dp = dp[next];
                max_next = next;
            }
    }

    int res = max_dp + 1;
    return dp[curr] = res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n; cin >> n;

    for (int i = 0; i < n; i++) {
        int idx; 
        cin >> idx;

        cin >> A[idx];
    }

    for (int i = SIZE_N - 1; i > 0; i--)
        f(i);
    
    cout << n - *max_element(dp.begin(), dp.end());

    return 0;
}