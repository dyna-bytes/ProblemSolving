/* I got an idea from the below link
 * https://eine.tistory.com/entry/%EB%B0%B1%EC%A4%80-1006%EB%B2%88-%EC%8A%B5%EA%B2%A9%EC%9E%90-%EC%B4%88%EB%9D%BC%EA%B8%B0-%EB%AC%B8%EC%A0%9C-%ED%92%80%EC%9D%B4
 */
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
const int INF = 987654321;

int T, N, W;
int lim_N, phase;
int room[10000 + 3][2];
int dp[10000 + 1][4];

/**
 * @brief 
 * 입력: 남은 구역의 모양(현재 침투할 column, 이전 구역의 모양)
 * 출력: 최소 특수 소대의 합
 * 
 * 취할 수 있는 행동: 
 * 0. 이전 열의 위-아래 두 칸이 모두 채워진 경우:
 *      위 한 칸, 위-오른쪽 두 칸, 위-아래 두 칸
 * 1. 현재 열의 위 한 칸만 채워진 경우:
 *      아래 한 칸, 아래-오른쪽 두 칸
 * 2. 현재 열의 아래 한 칸만 채워진 경우:
 *      위 한 칸, 위-오른쪽 두 칸
 * 3. 현재 열의 위-오른쪽 두 칸이 모두 채워진 경우:
 *      아래 한 칸, 아래-오른쪽 두 칸
 * 4. 현재 열의 아래-오른쪽 두 칸이 모두 채워진 경우:
 *      이러한 상황이 존재하지 않음(위에서 부터 채워나가므로)
 */
int specialForce(int col, int status){
    if(dp[col][status] != -1) return dp[col][status];
    if(col == lim_N) return 0;
    
    int minSum = INF;
    switch (status)
    {
    case 0: // 0. 이전 열의 위-아래 두 칸이 모두 채워진 경우:
        // 위-오른쪽 두 칸 차지
        if(room[col][0] + room[col + 1][0] <= W)
            minSum = min(minSum, 1 + specialForce(col, 3));
        // 위-아래 두 칸 차지
        if(room[col][0] + room[col][1] <= W)
            minSum = min(minSum, 1 + specialForce(col + 1, 0));
        // 위 한 칸 차지
        if(room[col][0] <= W)
            minSum = min(minSum, 1 + specialForce(col, 1));
        break;
    case 1: // 1. 현재 열의 위 한 칸만 채워진 경우:
        // 아래-오른쪽 두 칸 차지
        if(room[col][1] + room[col + 1][1] <= W)
            minSum = min(minSum, 1 + specialForce(col + 1, 2));
        // 아래 한 칸 차지
        if(room[col][1] <= W)
            minSum = min(minSum, 1 + specialForce(col + 1, 0));
        break;
    case 2: // 2. 현재 열의 아래 한 칸만 채워진 경우:
        // 위-오른쪽 두 칸 차지
        if(room[col][0] + room[col + 1][0] <= W)
            minSum = min(minSum, 1 + specialForce(col + 1, 1));
        // 위 한 칸 차지
        if(room[col][0] <= W)
            minSum = min(minSum, 1 + specialForce(col + 1, 0));
        break;
    case 3: // 3. 현재 열의 위-오른쪽 두 칸이 모두 채워진 경우:
        // 아래-오른쪽 두 칸 차지
        if(room[col][1] + room[col + 1][1] <= W)
            minSum = min(minSum, 1 + specialForce(col + 2, 0));
        // 아래 한 칸 차지
        if(room[col][1] <= W)
            minSum = min(minSum, 1 + specialForce(col + 1, 1));
        break;
    }

    return dp[col][status] = minSum;
}

void trackAnswer(int col, int status){
    if(col == lim_N) return;
    cout << "col: " << col << " status: " << status;
    switch (status)
    {
    case 0:
        if(specialForce(col, status) == 1 + specialForce(col, 3)){
            cout << " next col: " << col << " choice: " << 3 << endl;
            trackAnswer(col, 3);
        }
        else if(specialForce(col, status) == 1 + specialForce(col + 1, 0)){
            cout << " next col: " << col + 1 << " choice: " << 0 << endl;
            trackAnswer(col + 1, 0);
        }
        else if(specialForce(col, status) == 1 + specialForce(col, 1)){
            cout << " next col: " << col << " choice: " << 1 << endl;
            trackAnswer(col, 1);
        }
        break;
    case 1:
        if(specialForce(col, status) == 1 + specialForce(col + 1, 2)){
            cout << " next col: " << col + 1 << " choice: " << 2 << endl;
            trackAnswer(col + 1, 2);
        }
        else if(specialForce(col, status) == 1 + specialForce(col + 1, 0)){
            cout << " next col: " << col + 1 << " choice: " << 0 << endl;
            trackAnswer(col + 1, 0);
        }
        break;
    case 2:
        if(specialForce(col, status) == 1 + specialForce(col + 1, 1)){
            cout << " next col: " << col + 1 << " choice: " << 1 << endl;
            trackAnswer(col + 1, 1);
        }
        else if(specialForce(col, status) == 1 + specialForce(col + 1, 0)){
            cout << " next col: " << col + 1 << " choice: " << 0 << endl;
            trackAnswer(col + 1, 0);
        } 
        break;
    case 3:
        if(specialForce(col, status) == 1 + specialForce(col + 2, 0)){
            cout << " next col: " << col + 2 << " choice: " << 0 << endl;
            trackAnswer(col + 2, 0);
        }
        else if(specialForce(col, status) == 1 + specialForce(col + 1, 1)){
            cout << " next col: " << col + 1 << " choice: " << 1 << endl;
            trackAnswer(col + 1, 1);
        }
        break;    
    }
}

int main(){
    cin >> T;
    while(T--){
        cin >> N >> W;
        for(int i = 0; i < N; i++)
            cin >> room[i][0];
        for(int i = 0; i < N; i++)
            cin >> room[i][1];

        lim_N = N;
        room[N][0] = INF;
        room[N][1] = INF;

        memset(dp, -1, sizeof(dp));
        int ret = specialForce(0, 0);

        if(N > 1){
            // 0열과 N-1열의 위 두 칸이 이미 차지 됨
            if(room[0][0] + room[N-1][0] <= W){
                int tmp1 = room[0][0];
                int tmp2 = room[N-1][0];
                
                room[0][0] = room[N-1][0] = W;
                
                memset(dp, -1, sizeof(dp));
                ret = min(ret, specialForce(0, 1));
                
                room[0][0] = tmp1;
                room[N-1][0] = tmp2;
            }
            // 0열과 N-1열의 아래 두 칸이 이미 차지 됨
            if(room[0][1] + room[N-1][1] <= W){
                int tmp1 = room[0][1];
                int tmp2 = room[N-1][1];
                
                room[0][1] = room[N-1][1] = W;

                memset(dp, -1, sizeof(dp));
                ret = min(ret, specialForce(0, 2));
                
                room[0][1] = tmp1;
                room[N-1][1] = tmp2;
            }
            // 0열과 N-1열의 위 두 칸, 아래 두 칸이 이미 차지 됨
            if((room[0][0] + room[N-1][0] <= W) && (room[0][1] + room[N-1][1] <= W)){
                room[0][0] = room[N-1][0] = room[0][1] = room[N-1][1] = W;
                
                memset(dp, -1, sizeof(dp));
                ret = min(ret, specialForce(1, 0));
            }
        }
        cout << ret << '\n';
    }

    return 0;
}