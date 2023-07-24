#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vint;
typedef vector<ll> vll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;

#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define debug(x) cout << "[Debug] " << #x << " is " << x << endl
#define _debugV1(v) for (auto it = v.begin(); it != v.end(); ++it) { cout << *it; if (next(it) != v.end()) cout << " | "; }
#define debugVec(v) do { \
    cout << "[Debug] [ "; \
    _debugV1(v); \
    cout << " ]" << endl; \
} while (0)
#define debugV2(v) do { \
    cout << "[Debug] [" << endl; \
    for (auto v1: v) { \
        cout << "  [ "; \
        _debugV1(v1); \
        cout << " ]" << endl; \
    } \
    cout << "]" << endl; \
} while (0)
#define pair_out(pair) cout << '{' << pair.first << ", " << pair.second << '}' 

pii solve(int N, int X, vint& pSum) {
    int maxSum = 0;
    int count = 1;
    for (int i = 0; i + X <= N; i++) {
        int sum = pSum[i + X] - pSum[i];
        if (maxSum == sum) 
            count++;
        if (maxSum < sum) 
            maxSum = sum, count = 1;
    }
    return {maxSum, count};
}
int main() {
    FASTIO;
    int N, X;
    cin >> N >> X;
    vint pSum(N+1); // pSum[n]: n개 원소의 합

    int visitor;
    for (int i = 0; i < N; i++) {
        cin >> visitor;
        pSum[i+1] = pSum[i] + visitor;
    }
    pii ret = solve(N, X, pSum);

    if (ret.first == 0) cout << "SAD" << endl;
    else cout << ret.first << "\n" << ret.second << endl;
    return 0;
}