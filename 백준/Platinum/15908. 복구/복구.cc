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
    vint fixed(N+1), fixed_psum(N+2), cnt_to_idx(N+2);
    vint dp(N+2), dp_rpsum(N+3); // 역방향 dp 누적합
    
    for (int i = 1; i <= N+1; i++) {
        if (B[i] > val) fixed[i] = true;
        // 지울 수 없는 수의 개수의 누적합. i까지 지울 수 없는 수의 개수
        fixed_psum[i] = fixed_psum[i-1] + fixed[i];
        // 지울 수 없는 수의 개수에 따른 인덱스 i
        if (fixed[i]) cnt_to_idx[fixed_psum[i]] = i;
    }

    dp[N+1] = true; // i = N+1을 base case로 생각하는 것이 편리. l과 r 역시 최대범위를 N+1로 잡는다.
    dp_rpsum[N+1] = 1; // dp_rpsum[i] = dp_rpsum[i+1] + dp[i]
    // dp[i] + dp[i+1] + ... + dp[j] = dp_rsum[i] - dp_rsum[j+1]

    int l, r;
    for (int i = N; i > 0; i--) {
        if (!fixed[i] && dp[i+1]) dp[i] = true;
        else if (i + A[i] <= N+1) { // max(l) == N+1
            // 아무 숫자도 지우지 않음. 현재 인덱스 위치 + 헤더의 사이즈
            l = i + A[i];

            // 현재 위치에서부터 지울 수 있는 숫자를 최대한 지움.
            // <=> 현재 위치에서부터 지울 수 없는 숫자를 A[i]개 사용.
            int max_fixed_cnt = fixed_psum[i] + A[i];
            if (max_fixed_cnt > fixed_psum[N]) r = N+1; // max(r) == N+1
            else r = cnt_to_idx[max_fixed_cnt];

            // dp[l, r] 사이에 true가 하나라도 있으면 dp[i] 역시 true
            if (l <= r) dp[i] = (dp_rpsum[l] - dp_rpsum[r+1] > 0);
        }
        
        dp_rpsum[i] = dp_rpsum[i+1] + dp[i];
    }
    return dp[1];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> N;
    A.resize(N+1), B.resize(N+1);
    for (int i = 1; i <= N; i++) cin >> A[i];
    for (int i = 1; i <= N; i++) cin >> B[i];
    
    int lo = -1, hi = 100000;
    while (lo + 1 < hi) {
        int mid = (lo + hi)/2;
        if (f(mid)) hi = mid;
        else lo = mid;
    }
    cout << hi << endl;
    return 0;
}