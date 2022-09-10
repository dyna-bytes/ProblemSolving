#include <iostream>
#include <cstring>
using namespace std;
#define debug(x) cout << "[Debug] " << #x << " is " << x << '\n'

typedef unsigned long long ull;

int N, M;
ull K;
ull dp[202][202];
char res[102];
int p;

ull C(int n, int r){
    ull &ret = dp[n][r];
    if(ret) return ret;
    if(n == r || r == 0) return ret = 1;

    ret = C(n-1, r) + C(n-1, r-1);
    return ret;
}

void get_Nth_bit(int n, int m, ull k){
    if(n == 0){
        for(int i = 0; i < n+m; i++) res[p++] = 'z';
        return;
    }
    if(m == 0){
        for(int i = 0; i < n+m; i++) res[p++] = 'a';
        return;
    }
    // debug(n);
    // debug(m);
    // debug(k);
    // debug((C(n+m-1, m)));    
    
    if(k < C(n+m-1, m)){
        res[p++] = 'a';
        get_Nth_bit(n-1, m, k);
    }
    else{
        res[p++] = 'z';
        get_Nth_bit(n, m-1, k - C(n+m-1, m));
    }
}

int main(){
    memset(dp, 0, sizeof(dp));
    cin >> N >> M >> K;

    if(K > C(N+M, M)){
        cout << -1;
        return 0;
    }

    get_Nth_bit(N, M, K-1);

    for(int i = 0; i < N+M; i++) cout << res[i];

}