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

int solve(int N, int M, vint& A) {
    int ret = 0;
    int s = 0, e = 0;

    // 구간 [s, e)의 부분합이 M인지 체크
    int m = 0;
    for (; s < N; ) {
        if (m >= M || e == N) 
            m -= A[s++];
        else if (m < M) 
            m += A[e++];

        if (m == M) ret++;
    }
    return ret;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int N, M; cin >> N >> M;

    vint A(N);
    for (int i = 0; i < N; i++) cin >> A[i];
    
    cout << solve(N, M, A);

    return 0;
}