#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vint;
const int MOD = 9901;

int Y, X;
vector<vint> dp;

int f(int idx, int status) {
    int& ret = dp[idx][status];
    if (ret != -1) return ret;

    if (idx == Y*X) return ret = (status == 0);

    ret = 0;
    // 블럭을 놓을 수 없는 경우
    if (status & (1 << 0)) 
        return ret = f(idx+1, status >> 1);
    
    // 1x2 가로 도미노 시도
    if ((idx % X != X-1) && ((status & (1 << 1)) == 0)) 
        ret += f(idx+2, status >> 2);

    // 2x1 세로 도미노 시도
    ret += f(idx+1, (status >> 1) | (1 << X - 1));
    return ret %= MOD;
}

int main() {
    cin >> Y >> X;
    dp.resize(Y*X + 1, vint(pow(2, X + 1), -1));
    cout << f(0, 0);

    return 0;
}