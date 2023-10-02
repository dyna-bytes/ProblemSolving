#include <iostream>
#include <cstring>
using namespace std;

typedef unsigned long long ull;
int N, K;
ull dp[201][201];

ull H(int n, int r){
    ull &ret = dp[n][r];
    if(ret) return ret;
    if(n == 0 || r == 0) return ret = 1;

    ret = H(n, r-1) + H(n-1, r);
    return ret = ret % 1000000000;
}

int main(){
    cin >> N >> K;
    cout << H(N, K-1);
    // f(N, K) = H(N, K-1)
    // 정수 K개를 더하여 그 합이 N이 되게 하는 경우의 수는
    // 1을 N개 늘여놓고, N개의 빈 공간(첫번째 1보다 앞 부터 마지막 1의 앞까지)에 
    // K-1개의 슬래시를 둘 때의 경우의 수와 동치이다.
}