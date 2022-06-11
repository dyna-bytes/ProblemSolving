#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

int N, L;
unsigned I;
unsigned dp[32][32];
char b[33];
int p;

unsigned combination(int n, int r){
    unsigned &ret = dp[n][r];
    if(ret) return ret;
    if(n == 0 || r == 0) return ret = 1;
    
    ret = combination(n-1, r);
    if(r > 0) ret += combination(n-1, r-1);
    return ret;
}

void get_Nth_bit(int n, int l, unsigned i){
    if(n == 0) return;
    if(l == 0){
        for(int j = 0; j < n; j++) b[p++] = '0';
        return;
    }

    if(i < combination(n-1, l)){
        b[p++] = '0';
        get_Nth_bit(n-1, l, i);
    }
    else{
        b[p++] = '1';
        get_Nth_bit(n-1, l-1, i - combination(n-1, l));
    }
}

int main(){
    cin >> N >> L >> I;
    memset(dp, 0, sizeof(dp));
    get_Nth_bit(N, L, I-1);

    for(int i = 0; i < N; i++)
        cout << b[i];

    return 0;
}