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
typedef vector<ll> vll;
typedef vector<pii> vpii;

int N;
ll K;
vector<vll> dp;

// 길이가 n이고 닫히지 않은 "("이 r개인 집합의 크기
ll G(int n, int r) {
    if (n == 0) return (r == 0);

    ll& ret = dp[n][r];
    if (ret != -1) return ret;

    ret = G(n-1, r+1);
    if (r > 0) ret += G(n-1, r-1);
    return ret; 
}

// 길이가 n-1이고, 닫히지 않은 "("이 r+1개
// 이번에 '('으로 열어보는 집합의 크기로 k가 커버 가능한가?
void f(int n, int r, ll k) {
    if (n == 0) return;

    ll pivot = G(n-1, r+1);
    if (k >= pivot) { // 여는 괄호로 시작하는 집합이 전부 커버 가능하다면
        cout << ')';  // 사전 순으로 해당 집합의 바로 다음에 있는 닫는 괄호로 시작해야 한다.
        f(n-1, r-1, k-pivot);
    } else {
        cout << '(';
        f(n-1, r+1, k);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> N >> K;
    dp.resize(N+1, vll(N+1, -1));

    if (K >= G(N, 0)) cout << -1;
    else f(N, 0, K);
    return 0;
}