#include <iostream>
// #include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <cstring>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define endl '\n'
typedef long long ll;

/**
 * @brief Bottom-up DP
 * 
 * Let DP[x][y]: 왼쪽 카드 더미에 x장, 오른쪽 카드 더미에 y장이 있을 때
 * 선공이 이기면 1, 후공이 이기면 0
 * 
 * Base Case: DP[0][0] = 1
 * 
 * [DP[x][y]를 결정하는 문제]
 * 왼쪽 카드가 x장, 오른쪽 카드가 y장 남아있을 때, 
 * 선공이 왼쪽 카드를 적당히 가져가서 x장을 j장으로 만들었다고 하자.
 * 
 * 선공이 왼쪽 카드를 가져갈 수 있는 모든 경우에 대해 후공이 이겨버린다면
 * (DP[j][y] = 1, DP[j+1][y] = 1, ... DP[x-1][y] = 1 이라면)
 * 이때의 선공은 항상 질 수 밖에 없을 것이다. (DP[x][y] = 0)
 * 
 * 오른쪽 카드 더미에 대해서도 마찬가지이다. 
 * 위 두 경우에 대해 모든 값이 1이라면 DP[x][y] = 0이고, 그렇지 않다면 DP[x][y] = 1이다.
 * 
 */
const int MAX = 3005;
int dp[MAX][MAX];
int pr[MAX][MAX], qr[MAX][MAX]; // dp 누적합
int px[MAX], qx[MAX]; // 특정한 x에 대해 가능한 j
int p[MAX], q[MAX];

void solve(){
    memset(dp, 0, sizeof(dp));    
    memset(pr, 0, sizeof(pr));    memset(qr, 0, sizeof(qr));
    memset(px, 0, sizeof(px));    memset(qx, 0, sizeof(qx));
    memset(p, 0, sizeof(p));    memset(q, 0, sizeof(q));

    int N, K; cin >> N >> K;
    for(int i = 1; i <= N; i++) cin >> p[i];
    for(int i = 1; i <= N; i++) cin >> q[i];

    dp[0][0] = 1;

    // 특정한 x에 대해 가능한 j를 투포인터로 미리 찾아놓기
    int j = 1, sum_j_i = 0;
    for(int i = 1; i <= N; i++){
        sum_j_i += p[i];

        // (j, y) ~ (i, y)의 합이 K를 넘지 않는 (x, y)
        // : [j, i] 구간의 p[x] 합이 K를 넘지 않도록 유지함
        while(sum_j_i > K) sum_j_i -= p[j++];
        px[i] = j - 1;
    }

    j = 1, sum_j_i = 0;
    for(int i = 1; i <= N; i++){
        sum_j_i += q[i];

        while(sum_j_i > K) sum_j_i -= q[j++];
        qx[i] = j - 1;
    }

    int awin = 0, bwin = 0;
    for(int i = 0; i <= N; i++){
        for(int j = 0; j <= N; j++){
            int pt = 0, qt = 0;
            if (i) pt = pr[i - 1][j] - (px[i] ? pr[px[i] - 1][j] : 0);
            if (j) qt = qr[i][j - 1] - (qx[j] ? qr[i][qx[j] - 1] : 0);
            if (pt < i - px[i] || qt < j - qx[j]) dp[i][j] = 1;
            
            (dp[i][j] ? awin : bwin)++;
            pr[i][j] = (i ? pr[i - 1][j] : 0) + dp[i][j];
            qr[i][j] = (j ? qr[i][j - 1] : 0) + dp[i][j];
        }
    }

    cout << awin << " " << bwin << endl;
    // int s = 0;
    // for(int i = 0; i <= N; i++)
    //     for(int j = 0; j <= N; j++)
    //         s += dp[i][j];
    // cout << s << ' ' << (N+1)*(N+1) - s << endl;
};

int main(int argc, char** argv){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    // freopen("input.txt", "r", stdin);

    int T, test_case;

    cin >> T;
    for(test_case = 0; test_case < T; test_case++){
        // Print the answer to standard output(screen).
        cout << "Case #" << test_case+1 << endl;
        solve();
        cout.flush();
    }

    return 0;
}