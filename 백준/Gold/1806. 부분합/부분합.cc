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

int solve(int N, int S, vint& nums) {
    int min_len = N + 1;
    int p_sum = 0;
    int s = 0, e = 0;
    for (; e < N; ) {
        if (p_sum < S) p_sum += nums[e++];
        else if (p_sum >= S) {
            min_len = min(min_len, e - s);
            p_sum -= nums[s++];
        }
    }

    for (; s < N; ) {
        if (p_sum >= S) min_len = min(min_len, e - s);
        p_sum -= nums[s++];
    }

    return min_len == N + 1 ? 0 : min_len;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int N, S;
    cin >> N >> S;
    vint A(N);
    for (int i = 0; i < N; i++) cin >> A[i];
    cout << solve(N, S, A);

    return 0;
}