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
typedef vector<ll> vll;
typedef vector<pii> vpii;
const int MOD = 1e9 + 7;

int Y, X, L;
string word;
vector<vector<char>> board;
vector<vector<vll>> dp;

// y1, x1, y2, x2: 상하좌우 각 모서리
// 사각형 영역 [y1, y2] * [x1, x2]의 dp 합
ll sum (int idx, int y1, int x1, int y2, int x2) {
    y1 = max(1, y1);
    x1 = max(1, x1);
    y2 = min(Y, y2);
    x2 = min(X, x2);
    ll ret = 0;
    ret += dp[idx][y2][x2];
    ret -= dp[idx][y1-1][x2];
    ret -= dp[idx][y2][x1-1];
    ret += dp[idx][y1-1][x1-1];
    return (ret + 2LL * MOD) % MOD;
}

ll solve() {
    // dp[i][y][x]: 단어의 i번째 글자까지 봤을 때, 원점부터 좌표 (y, x)까지 계산한 경우의 수의 누적합
    // dp[][0][0]에 padding을 넣어 one-based index로 관리한다.

    // base case: 단어의 첫번째 글자로 시작 가능 => 경우의 수 1 추가
    for (int y = 1; y <= Y; y++)
        for (int x = 1; x <= X; x++) {
            dp[0][y][x] = dp[0][y-1][x] + dp[0][y][x-1] - dp[0][y-1][x-1];
            if (board[y-1][x-1] == word[0]) dp[0][y][x]++;
        }

    for (int i = 1; i < L; i++)
        for (int y = 1; y <= Y; y++) {
            for (int x = 1; x <= X; x++) {
                // 만약 현재 자리를 유니콘이 밟을 수 있다면
                if (board[y-1][x-1] == word[i]) {
                    // 이전에 유니콘이 출발할 수 있는 모든 영역의 경우의 수의 합
                    // == 현재 자리에 유니콘이 도달할 수 있는 경우의 수
                    dp[i][y][x] = sum(i-1, 1, 1, Y, X);         // 전체
                    dp[i][y][x] -= sum(i-1, y-1, 1, y+1, X);    // 가로 3줄 전체
                    dp[i][y][x] -= sum(i-1, 1, x-1, Y, x+1);    // 세로 3줄
                    dp[i][y][x] -= sum(i-1, y-2, x-2, y+2, x+2);// 5 * 5 정사각형
                    dp[i][y][x] += sum(i-1, y-2, x-1, y+2, x+1);// 5 * 3 직사각형
                    dp[i][y][x] += sum(i-1, y-1, x-2, y+1, x+2);// 3 * 5 직사각형
                }
                // dp[y][x] = [1, y] * [1, x] 영역의 경우의 수 누적합으로 유지함
                // 2차원 prefix sum이므로 원할 때 뺄셈을 통해 원하는 영역의 dp 합을 O(1)에 구할 수 있음
                dp[i][y][x] += dp[i][y-1][x];
                dp[i][y][x] += dp[i][y][x-1];
                dp[i][y][x] -= dp[i][y-1][x-1];
                (dp[i][y][x] += 2LL * MOD) %= MOD;
            }
        }
    return dp[L-1][Y][X];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> Y >> X >> L;

    cin >> word;
    L = (int)word.size();

    board.resize(Y+1, vector<char>(X+1));
    dp.resize(L+1, vector<vll>(Y+1, vll(X+1)));

    for (int y = 0; y < Y; y++) {
        string inp; cin >> inp;
        for (int x = 0; x < X; x++)
            board[y][x] = inp[x];
    }    
    cout << solve();
    
    return 0;
}