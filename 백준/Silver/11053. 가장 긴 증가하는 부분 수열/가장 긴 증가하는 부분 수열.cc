#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int N;
int A[1001];
int LIS[1001]; // LIS[pos] : pos번 째 항을 반드시 포함한 부분증가수열의 길이
/*
  A   = [25,  30,   10,   20,   50]
 LIS:    [0]  [1]   [2]   [3]   [4]
        ____  ____  ____  ____  ____
          |    |     |     |     |  
        [25]  [30]  [10]  [20]  [50]
        [30]  [50]  [20]  [50]
        [50]        [50]
*/

int lis(int pos){
    if(pos == N-1) return LIS[pos] = 1;
    
    // A[next] > A[pos], pos > next를 만족하는 최소의 A[next] 값과 그 때의 next 값을 찾음
    
    // A[next] > A[pos], pos > next 중에서, LIS[next]의 값이 최대일 때의 next 값을 찾음
    int max_LIS = 0;
    int max_next = 0;
    // int min_A = 987654321;
    // int min_next = N;
    for(int next = pos + 1; next < N; next++){
        if(A[next] > A[pos]){
            if(max_LIS < LIS[next]){
                max_LIS = LIS[next];
                max_next = next;
            }
        }
    }
    int res = (max_next == 0)? 1 : LIS[max_next] + 1;
    return LIS[pos] = res;
}

int main(){
    cin >> N;
    for(int i = 0; i < N; i++)
        cin >> A[i];

    for(int i = N-1; i >= 0; i--)
        lis(i);

    int res = 0;
    for(int i = 0; i < N; i++)   
        res = max(res, LIS[i]);
    cout << res; 

    // cout << endl;
    // for(int i = 0; i < N; i++)
    //     cout << LIS[i] << " ";

    return 0;
}