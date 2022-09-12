#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;
using ll = long long;
#define SIZE (100+2)
ll dp[SIZE][2];

// 길이가 N이고, 첫 자리가 digit인 이친수의 개수
ll pinary(int n, bool digit){
    ll &ret = dp[n][digit];
    if(ret != -1) return ret;
    if(n == 1) return ret = 1;

    if(digit) ret = pinary(n-1, 0);
    else ret = pinary(n-1, 1) + pinary(n-1, 0);
    return ret;
}

// K번째 이친수가 N자리 임을 반환
int findN(ll K){
    int N = 0;
    for(ll sum = 0; sum < K; ){
        N++;
        sum += pinary(N, 1);
    }
    return N;
}

// N자리 이하의 이친수 개수 합
ll findK(int N){
    ll K = 0;
    for(int n = 0; n < N; ){
        n++;
        K += pinary(n, 1);
    }
    return K;
}

void trackAnswer(int N, ll K){
    if(N == 1){
        if(K == 0LL)      cout << 0;
        else if(K == 1LL) cout << 1;
        return;
    }
    // if(N == 2){
    //     if(K == 0LL)      { cout << 0; cout << 0; }
    //     else if(K == 1LL) { cout << 0; cout << 1; }
    //     else if(K == 2LL) { cout << 1; cout << 0; }
    //     return;
    // }
    
    
    if(K > findK(N-1)){
        cout << 1;
        trackAnswer(N-1, K - findK(N-1) - 1);
    }
    else{
        cout << 0;
        trackAnswer(N-1, K);
    }
}

int main(){
    memset(dp, -1, sizeof(dp));
    ll K;
    int N;
    cin >> K;
    // if(K == 1){
    //     cout << 1;
    //     return 0;
    // }

    N = findN(K);
    trackAnswer(N, K);

    return 0;
}