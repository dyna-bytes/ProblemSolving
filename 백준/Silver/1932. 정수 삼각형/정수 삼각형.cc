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

const int MAXS = 125250;

// all indices are one-based
int triangle[MAXS + 1];
int level_size[500 + 1];
int dp[MAXS + 1];

int f(int y, int curr) {
    if (y == 1) return triangle[1];
    int& ret = dp[curr];
    if (ret) return ret;

    int left = curr - y;
    int right = curr - (y - 1);
    
    if (left > level_size[y - 2]) ret = max(ret, f(y - 1, left));
    if (right <= level_size[y - 1]) ret = max(ret, f(y - 1, right));
    
    ret += triangle[curr];
    return ret;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N; cin >> N;
    int n = 0;
    for (int y = 1; y <= N; y++) {
        for (int x = 1; x <= y; x++)
            cin >> triangle[++n];
        level_size[y] = n;
    }
    
    int res = 0;
    for (int i = level_size[N - 1] + 1; i <= level_size[N]; i++) 
        res = max(res, f(N, i));
    
    cout << res;
    return 0;
}