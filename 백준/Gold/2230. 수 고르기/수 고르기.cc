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
const int INF = 2e9 + 1;

int solve(int N, int M, vint& A) {
    sort(A.begin(), A.end());
    A.push_back(INF); // dummy 항 추가(segfault 방지)

    int ret = INF;
    int diff;
    int s = 0, e = 0;
    for (; e < N; ) {
        diff = A[e] - A[s];
        if (diff < M) e++;
        else if (diff >= M) {
            s++;
            ret = min(ret, diff);
        }
    } 

    for (; s < N; ) {
        diff = A[e] - A[s];
        s++;

        if (diff >= M) ret = min(ret, diff);
    }
    return ret;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int N, M;
    cin >> N >> M;
    vint A(N);
    for (int i = 0; i < N; i++) cin >> A[i];
    
    cout << solve(N, M, A);
    return 0;
}