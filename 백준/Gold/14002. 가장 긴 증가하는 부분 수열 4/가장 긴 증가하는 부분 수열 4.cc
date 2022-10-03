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

void solve (int N, vint& A) {
    int res = 0;
    vint dp(N, 1);
    vint history(N, -1);

    int last = 0;
    for (int curr = 0; curr < N; curr++) {
        
        for (int prev = 0; prev < curr; prev++) {
            if (A[curr] > A[prev]) 
                if (dp[curr] < dp[prev] + 1) {
                    dp[curr] = dp[prev] + 1;
                    history[curr] = prev;
                }
        }

        res = max(res, dp[curr]);
        if (res == dp[curr]) last = curr;
    }

    cout << res << endl;
    vint ans;
    for (int curr = last; curr != -1; curr = history[curr])
        ans.push_back(A[curr]);

    reverse(ans.begin(), ans.end());
    for (int a: ans) cout << a << " ";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N;
    cin >> N;
    vint A(N);
    for (int i = 0; i < N; i++) cin >> A[i];

    solve(N, A);
    return 0;
}