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
#define ADD 0
#define SUB 1
#define MUL 2
#define DIV 3

int N;
int A[12];
int add, sub, mul, divide;
int ops[12];

pii maxmin(const pii& a, const pii& b) {
    return { max(a.first, b.first), min(a.second, b.second) };
}

pii dfs(int n, int a, int s, int m, int d) {
    if (n + 1 == N) {
        int res = A[0];
        for (int i = 0; i < N - 1; i++) {
            if (ops[i] == ADD) res = res + A[i+1];
            else if (ops[i] == SUB) res = res - A[i+1];
            else if (ops[i] == MUL) res = res * A[i+1];
            else if (ops[i] == DIV) res = res / A[i+1];
        }
        return { res, res };   
    }

    pii res = { INT_MIN, INT_MAX };
    if (a > 0) {
        ops[n] = ADD;
        res = maxmin(res, dfs(n+1, a-1, s, m, d));
    }
    if (s > 0) {
        ops[n] = SUB;
        res = maxmin(res, dfs(n+1, a, s-1, m, d));
    }
    if (m > 0) {
        ops[n] = MUL;
        res = maxmin(res, dfs(n+1, a, s, m-1, d));
    }
    if (d > 0) {
        ops[n] = DIV;
        res = maxmin(res, dfs(n+1, a, s, m, d-1));
    }
    return res;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> N;
    for (int i = 0; i < N; i++) cin >> A[i];
    cin >> add >> sub >> mul >> divide;

    pii res = dfs(0, add, sub, mul, divide);
    cout << res.first << endl;
    cout << res.second << endl;
    return 0;
}