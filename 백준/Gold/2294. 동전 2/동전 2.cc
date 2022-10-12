#include <iostream>
#include <cstring>
using namespace std;

#define MAX_k 10001
#define MAX_n 101
#define IMPOSSIBLE 10001
#define MAX_COST 100001

int dp[MAX_n][MAX_k];
int price[MAX_n];

int N, k;

/*min function*/
int min(int A, int B) {
   if (A > B) return B;
   else return A;
}

/*major function*/
/*n번째 종류 동전11, 잔금 k*/
int func(int n, int k) {
   if (n == N) return (k == 0 ? 0 : IMPOSSIBLE);

   if (dp[n][k] != -1) return dp[n][k];

   int result = func(n + 1, k);
   if (k >= price[n]) result = min(result, func(n, k - price[n]) + 1);
   
   return dp[n][k] = result;
}

int main(void) {
   // n, k 입력받기
   cin >> N >> k;
   
   //dp[1][1] ~ dp[N][k] 초기화
//    for (int i = 0; i < N; i++)
//       for (int j = 0; j < k + 1; j++)
//          dp[i][j] = IMPOSSIBLE;
    memset(dp,-1, sizeof(dp));
   
   //n개 종류 입력 받기
   for (int i = 0; i < N; i++) cin >> price[i];

   //불가능한 경우 도출
   int x = func(0, k);
   if (x == IMPOSSIBLE) x = -1;

   //최종 결과 출력
   cout << x << endl;
}
