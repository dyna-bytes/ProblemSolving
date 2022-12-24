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
typedef vector<ll> vll;
typedef vector<vll> matrix;
const ll MOD = 1234567891;

matrix operator * (const matrix& A, const matrix& B) {
    assert(A[0].size() == B.size());
    int R = A.size(), K = B.size(), C = B[0].size();
    matrix M(R, vll(C));
    for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++)
            for (int k = 0; k < K; k++)
                (M[r][c] += A[r][k] * B[k][c] % MOD) %= MOD;
    return M;
}

matrix matpow(matrix A, ll N) {
    assert(A.size() == A[0].size());
    matrix ret(A.size(), vll(A.size()));
    for (int i = 0; i < A.size(); i++) ret[i][i] = 1; // ret = I

    while (N) {
        if (N & 1) ret = ret * A;
        A = A * A;
        N /= 2;
    }
    return ret;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    auto check = [&](string& str) {
        for (char& c: str)
            if (c != '4' && c != '7')
                return false;
        return true;
    };
    
    ll N, L; cin >> N >> L;
    ll cnt44 = 0, cnt47 = 0, cnt74 = 0, cnt77 = 0;
    unordered_set<string> nums;

    for (int i = 0; i < N; i++) {
        string str; cin >> str;
        if (!check(str)) continue;
        if (nums.find(str) != nums.end()) continue;
        nums.insert(str);

        if (str.front() == '4' && str.back() == '4') cnt44++;
        else if (str.front() == '4' && str.back() == '7') cnt47++;
        else if (str.front() == '7' && str.back() == '4') cnt74++;
        else if (str.front() == '7' && str.back() == '7') cnt77++;
    }

    matrix recurr = {
        {cnt44, cnt74},
        {cnt47, cnt77}
    };
    matrix base = {
        {cnt44 + cnt74},
        {cnt47 + cnt77}
    };

    auto res = matpow(recurr, L - 1) * base;
    cout << (res[0][0] + res[1][0]) % MOD << endl;
    // debugV2D(res);
    return 0;
}