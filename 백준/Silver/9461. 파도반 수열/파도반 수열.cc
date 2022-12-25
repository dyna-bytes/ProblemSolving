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

ll dp[101];

ll P(int n) {
    ll& ret = dp[n];
    if (ret) return ret;

    if (n <= 3) return ret = 1;
    if (n <= 5) return ret = 2;
    if (n == 6) return ret = 3;

    return ret = P(n - 1) + P(n - 5);
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        cout << P(N) << endl;
    }
    
    return 0;
}