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

void solve(int N, vint& A) {
    sort(A.begin(), A.end());

    int lo = A[0], hi = A[N-1];
    int s = 0, e = N-1;
    int min_abs_sum = INF;
    for (; s < e; ) {
        int sum = A[s] + A[e];
        if (min_abs_sum > abs(sum)) {
            min_abs_sum = abs(sum);
            lo = A[s], hi = A[e];
        }

        if (sum > 0) e--;
        else s++;
    }
    cout << lo << " " << hi;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int N; cin >> N;
    vint A(N);
    for(int& n: A) cin >> n;
    solve(N, A);
    return 0;
}