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

int solve(int N, int K, vint& A) {
    vint p_sum(N-K+1); // p_sum[i]: 구간[i, i+K]의 A 누적합

    for (int i = 0; i < K; i++)
        p_sum[0] += A[i];

    for (int i = 1; i <= N-K; i++)
        p_sum[i] = p_sum[i-1] - A[i-1] + A[i+K-1];

    int ret = INT_MIN;
    for (int i = 0; i <= N-K; i++)
        ret = max(ret, p_sum[i]);
    return ret;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N, K;
    cin >> N >> K;
    vint A(N);
    for(int& a: A) cin >> a;

    cout << solve(N, K, A);
    return 0;
}