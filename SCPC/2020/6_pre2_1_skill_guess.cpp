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

int N;
vector<ll> A, B;
vector<vector<ll>> dp;

/**
 * @brief A팀과 B팀에서 한 명씩을 제외하고 나머지를 적절히 매칭.
 * 제외된 인원은 서로 실력이 같아져서 실력 차가 0이 된다고 생각하자.
 * 
 * dp(i, 0): A팀의 i번째 멤버와 B팀의 i번째 멤버를 각각 매칭했을 때 실력 차의 합의 최솟값
 *  dp(i, 0) = dp(i+1, 0) + |A[i]-B[i]|
 * 
 * dp(i, 1): A팀에서 i+1번째 멤버를 제외하고, A팀의 i번째 멤버와 B팀의 i+1번째 멤버를 각각 매칭했을 때 실력 차의 최솟값
 *  dp(i, 1) = min{ dp(i+1, 1) + |A[i]-B[i+1]|, dp(i+1, 0) }
 *  예)
 *      A = [1, 2, 4, 5, 10]
 *      B = [1, 2, 3, 4, 5]
 * 
 * dp(i, 2): B팀에서 i+1번째 멤버를 제외하고, A팀의 i+1번째 멤버와 B팀의 i번째 멤버를 각각 매칭
 *  dp(i, 2) = min{ dp(i+1, 2) + |A[i+1]-B[i]|, dp(i+1, 0) }
 *  예)
 *      A = [1, 4, 5, 7, 8]
 *      B = [4, 5, 6, 7, 8]
 * 
 * dp(i, 3): A팀과 B팀에서 각각 한 명씩 제외하고, A팀의 i+1번째 멤버와 B팀의 i+1번째 멤버를 각각 매칭
 *  dp(i, 3) = min{ dp(i+1, 3), dp(i+1, 2), dp(i+1, 1) }
 *  예)
 *      A = [1, 4, 7, 8, 10]
 *      B = [4, 5, 6, 7, 8]
 */
ll getMinDiff(int n, int shift){
    ll& ret = dp[n][shift];
    if (ret != -1) return ret;
    if (n == N-1) {
        if (shift == 0) return ret = abs(A[n]-B[n]);
        return ret = 0;
    }

    if (shift == 0) ret = getMinDiff(n+1, 0) + abs(A[n]-B[n]);
    if (shift == 1) ret = min( getMinDiff(n+1, 1) + abs(A[n+1]-B[n]), getMinDiff(n+1, 0));
    if (shift == 2) ret = min( getMinDiff(n+1, 2) + abs(A[n]-B[n+1]), getMinDiff(n+1, 0));
    if (shift == 3) ret = min({ getMinDiff(n+1, 3) + abs(A[n]-B[n]), getMinDiff(n, 2), getMinDiff(n, 1) });
    
    return ret;
}

void solve(){
    cin >> N;
    A.clear(), B.clear();
    A.resize(N), B.resize(N);

    dp.clear();
    dp.resize(N+1, vector<ll>(4, -1));

    for(int i = 0; i < N; i++) cin >> A[i];
    for(int i = 0; i < N; i++) cin >> B[i];
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    ll ret = min(getMinDiff(0, 0), getMinDiff(0, 3));
    cout << ret << endl;
};

int main(int argc, char** argv){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int T, test_case;

    cin >> T;
    for(test_case = 0; test_case  < T; test_case++){
        
        cout << "Case #" << test_case+1 << endl;
        solve();
    }

    return 0;
}