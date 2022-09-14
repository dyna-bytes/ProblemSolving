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
vector<vint> dp;

// 구간 [s, e]의 최소 누적 비용 합
int f(int s, int e) {
    if (s + 1 == e) return 0;
    
    int& ret = dp[s][e];
    if (ret != -1) return ret;

    ret = INT_MAX;
    for (int m = s + 1; m < e; m++) 
        ret = min(ret, A[s]* A[m] * A[e] + f(s, m) + f(m, e));
    
    return ret;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> N;
    A.resize(N+1);
    dp.resize(N+1, vint(N+1, -1));

    int a, b; 
    for (int i = 0; i < N; i++) {
        cin >> a >> b;
        A[i] = a;
    }
    A[N] = b;
    
    cout << f(0, N);

    return 0;
}