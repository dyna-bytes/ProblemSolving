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
const int INF = 1e9;
#define NOT !

int N;
vector<vector<int>> cost(21, vector<int>(21));
vector<vector<int>> dp(21, vector<int>(1 << 21, -1));

int f(int x, int prev_state){
    int& ret = dp[x][prev_state];
    if(NOT(ret == -1)) return ret;
    if(x == N) return ret = 0;

    ret = INF;
    for(int y = 0; y < N; y++){
        // if NOT selected (y, x) before, try to choose it.
        if(NOT(prev_state & (1 << y))){
            int state = prev_state | (1 << y);
            ret = min(ret, f(x+1, state) + cost[y][x]);
        }
    }
    return ret;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> N;
    for(int y = 0; y < N; y++)
        for(int x = 0; x < N; x++)
            cin >> cost[y][x];

    cout << f(0, 0);    
    return 0;
}