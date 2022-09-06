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
vint A;
vector<vint> isPalindrome; // 구간 [s, e]에서 팰린드롬인가?

// bottom-up DP
void solve() {
    isPalindrome.resize(N+1, vint(N+1));
    
    // 길이가 1인 팰린드롬
    for (int i = 0; i < N; i++)
        isPalindrome[i][i] = true;

    // 길이가 2인 팰린드롬
    for (int i = 0; i < N-1; i++)
        if (A[i] == A[i+1]) isPalindrome[i][i+1] = true;

    // 길이가 k인 팰린드롬
    for (int k = 3; k <= N; k++)
        for (int e = k-1; e < N; e++) {
            int s = e - k + 1;
            if (A[s] == A[e] && isPalindrome[s+1][e-1])
                isPalindrome[s][e] = true;
        }
}

vector<vint> dp;
// top-down DP
int f(int s, int e) {
    int& ret = dp[s][e];
    if (ret != -1) return ret;

    if (s == e) return ret = true;
    if (s + 1 == e) return ret = (A[s] == A[e]);

    ret = (A[s] == A[e] && f(s+1, e-1));
    return ret;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> N;
    A.resize(N);

    for (int i = 0; i < N; i++) cin >> A[i];

    // solve();
    dp.resize(N+1, vint(N+1, -1));

    int M; cin >> M;
    for (int i = 0; i < M; i++) {
        int s, e; cin >> s >> e;
        s--, e--;
        if (f(s, e)) cout << 1 << endl;
        else cout << 0 << endl;
    }

    return 0;
}