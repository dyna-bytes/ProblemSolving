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

int N;
vint A, B;

bool f(int val) {
    vint fixed(N), fixed_psum(N+1), cnt_to_idx(N+1);
    vint dp(N+1), dp_rpsum(N+2); // 역방향 dp 누적합
  
    for (int i = 0; i < N; i++) {
        if (B[i] > val) fixed[i] = true;
        // 지울 수 없는 수의 개수의 누적합. i까지 지울 수 없는 수의 개수
        fixed_psum[i+1] = fixed_psum[i] + fixed[i];
        // 지울 수 없는 수의 개수에 따른 인덱스 i
        if (fixed[i]) cnt_to_idx[fixed_psum[i+1]] = i;
    }
    
    dp[N] = true; // i = N 을 base case로 생각하는 것이 편리. l과 r 역시 최대 N으로 잡는다.
    dp_rpsum[N] = 1; // dp_rpsum[i] = dp_rpsum[i+1] + dp[i]
    // dp[i] + dp[i+1] + ... + dp[j] = dp_rsum[i] - dp_rsum[j+1]
    int l, r;
    for (int i = N-1; i >= 0; i--) {
        if (!fixed[i] && dp[i+1]) dp[i] = true;
        else if (i + A[i] <= N) { // max(l) == N
            // 아무 숫자도 지우지 않음. 현재 인덱스 위치 + 헤더의 사이즈
            l = i + A[i];

            // 현재 위치에서부터 지울 수 있는 숫자를 최대한 지움.
            // <=> 현재 위치에서부터 지울 수 없는 숫자를 A[i]개 사용.
            int maximum_fixed_cnt = fixed_psum[i+1] + A[i];
            if (maximum_fixed_cnt > fixed_psum[N]) r = N; // max(r) == N
            else r = cnt_to_idx[maximum_fixed_cnt];

            // dp[l, r] 사이에 true가 하나라도 있으면 dp[i] 역시 true
            dp[i] = (dp_rpsum[l] - dp_rpsum[r+1] > 0);
        }; 

        dp_rpsum[i] = dp_rpsum[i+1] + dp[i];
    }
    return dp[0];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> N;
    A.resize(N+1), B.resize(N+1);
    for (int i = 0; i < N; i++) cin >> A[i];
    for (int i = 0; i < N; i++) cin >> B[i];
    
    int lo = -1, hi = 100000;
    while (lo + 1 < hi) {
        int mid = (lo + hi)/2;
        if (f(mid)) hi = mid;
        else lo = mid;
    }
    cout << hi;
    return 0;
}