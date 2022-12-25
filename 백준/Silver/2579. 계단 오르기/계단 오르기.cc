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

const int MAXN = 300;
int N;
int A[MAXN + 1];
int dp[2][MAXN + 1];

int f(int n, int cnt) {
    if (n == 0) return A[0];
    
    int& ret = dp[cnt][n];
    if (ret != -1) return ret;

    ret = 0;
    if (cnt == 0) ret = f(n - 1, cnt + 1);
    if (n > 1) ret = max(ret, f(n - 2, 0));
    ret += A[n];
    return ret;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    memset(dp, -1, sizeof(dp));
    cin >> N;
    for (int i = 0; i < N; i++) cin >> A[i];
    cout << f(N-1, 0);
    return 0;
}