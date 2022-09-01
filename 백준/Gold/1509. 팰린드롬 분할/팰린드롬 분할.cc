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
const int INF = 1e9 + 1;

int N;
vector<vint> isPalindrome(2501, vint(2501)); // isP[i][j]: 문자열 구간[i, j]가 팰린드롬인지 판별.
vint dp(2501, INF); // dp[i]: i번째 문자열까지 팰린드롬 분할 개수의 최솟값
// dp[e] = min(dp[e], dp[s-1] + 1) if (isP[s][e])

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    string S; cin >> S;
    N = S.length();
    
    // isPalindrome 전처리
    for (int i = 0; i < N; i++) // 문자열 구간[i, i]는 문자 하나이므로 팰린드롬이다.
        isPalindrome[i][i] = true; 

    for (int i = 0; i < N - 1; i++) // "AA", "BB", "CC" 역시 팰린드롬이다.
        if (S[i] == S[i + 1]) isPalindrome[i][i + 1] = true;

    // 길이가 k인 팰린드롬 문자열
    for (int k = 3; k <= N; k++)
        for (int s = 0; s <= N - k; s++) {
            int e = s + (k - 1);
            if (S[s] == S[e] && isPalindrome[s + 1][e - 1])
                isPalindrome[s][e] = true;
        }

    dp[0] = 1; // 0번째 문자열에 최소 1개가 있음
    for (int e = 0; e < N; e++)
        for (int s = 0; s <= e; s++) 
            if (isPalindrome[s][e]) 
                if (s == 0) dp[e] = 1;
                else dp[e] = min(dp[e], dp[s - 1] + 1);
            
        
    cout << dp[N-1];
    return 0;
}