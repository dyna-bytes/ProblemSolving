#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define endl '\n'
typedef long long ll;

const ll mod = 1e9 + 7;

ll Y, X;
char arr[3001][3001];
ll E[3001][3001];
ll S[3001][3001];
ll M[3001][3001];


int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> Y >> X;
    for(int y = 1; y <= Y; y++)
        for(int x = 1; x <= X; x++)
            cin >> arr[y][x];
    
    // E[y][x]: (y, x) 지점까지 E의 최대 개수
    // E[y][x] = E[y-1][x] + E[y][x-1] - E[y-1][x-1]
    // (y, x) 지점까지 E의 최대 개수가 곧 해당 지점에서 E로 시작할 수 있는 경우의 수이다.
    for(int y = 1; y <= Y; y++){
        for(int x = 1; x <= X; x++){
            E[y][x] = ((E[y][x-1] + E[y-1][x]) % mod - E[y-1][x-1] + mod) % mod;

            if(arr[y][x] == 'E') (E[y][x] += 1) %= mod;
        }
    }

    // S[y][x]: (y, x) 지점까지 E->S 경로를 만들 수 있는 경우의 수
    // (0, 0)부터 (y, x)까지 E와 S가 여러 개 있을 때,
    // 여러 E 중 단 하나와 여러 S 중 단 하나만을 고르면 된다.
    //
    // 1차원의 경우만 생각해 본다면
    // arr = [E, E, S, S, S] 일때, 현재의 S까지 오는 E->S 경로의 경우의 수는
    // 앞의 S까지 오는 E->S 경우의 수 + 앞의 E를 사용하고 현재의 S를 사용하여 만드는 E->S 경로의 경우의 수 이다.
    // 따라서, E->S 경로를 만들 수 있는 모든 경우의 수는
    // E = [1, 2, 2, 2, 2]
    // S = [0, 0, 2, 4, 6] 로 총 6가지 이다.
    for(int y = 1; y <= Y; y++){
        for(int x = 1; x <= X; x++){
            // 현재의 (y, x)까지 오는 모든 E->S 경로의 수
            S[y][x] = ((S[y][x-1] + S[y-1][x]) % mod - S[y-1][x-1] + mod) % mod;
            // 앞의 E에 현재의 S를 추가하여 만들 수 있는 경로의 수
            if(arr[y][x] == 'S') (S[y][x] += E[y][x]) % mod;
        }
    }
    
    for(int y = 1; y <= Y; y++){
        for(int x = 1; x <= X; x++){
            // 현재의 (y, x)까지 오는 모든 E->S->M 경로의 수
            M[y][x] = ((M[y][x-1] + M[y-1][x]) % mod - M[y-1][x-1] + mod) % mod;
            // 앞의 E->S 경로에 현재의 M을 추가하여 만들 수 있는 경로의 수
            if(arr[y][x] == 'M') (M[y][x] += S[y][x]) %= mod;
        }
    }
    
    cout << M[Y][X];
    return 0;
}