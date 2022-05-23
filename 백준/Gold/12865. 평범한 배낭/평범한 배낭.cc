/*
 * https://m.blog.naver.com/kks227/220777103650
 */

#include <iostream>
#include <vector>
using namespace std;

int N, K;
int W[100 + 1]; 
int V[100 + 1]; 
int dp[100 + 1][100000 + 1]; // [itemNum][limit] = valueSum

/*
 * itemNum번 보다 이전의 물품은 다 고려한 상태에서
 * 현재 가방에 남은 용량이 limit일 때
 * 앞으로 itemNum ~ N번 물품을 넣으면서 얻을 수 있는 최대 가치 합
 * 
 * ks(n, L) = max(ks(n+1, L - l_n) + v_n, ks(n+1, L))
 * 취할 수 있는 액션 : 현재 물건을 넣거나, 안 넣거나
 * 반환값 : 현재 물건의 가치와 이전 물건의 가치합의 합 (현재 물건을 넣은 경우)
 *          이전 물건만의 가치합 (현재 물건을 안 넣은 경우)
*/
int knapsack(int itemNum, int limit){
    if (itemNum == N || limit == 0) return 0;
    if (dp[itemNum][limit]) return dp[itemNum][limit];

    int valueSum = knapsack(itemNum + 1, limit); 
    if (limit - W[itemNum] >= 0)
        valueSum = max(valueSum, knapsack(itemNum + 1, limit - W[itemNum]) + V[itemNum]);
    return dp[itemNum][limit] = valueSum;
}

int main(){
    cin >> N >> K;
    for(int i = 0; i < N; i++){
        cin >> W[i];
        cin >> V[i];
    }

    cout << knapsack(0, K);
    return 0;
}