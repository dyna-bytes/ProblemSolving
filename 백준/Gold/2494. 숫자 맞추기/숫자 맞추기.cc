#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define endl '\n'
typedef long long ll;

int N;
int nums[10000+1];
int targets[10000+1];
vector<vector<int>> dp;

int digits(int pos, int offset){
    int& ret = dp[pos][offset];
    if(ret != -1) return ret;
    if(pos == N) return ret = 0;

    int n = (nums[pos] + offset) % 10;
    if(n < targets[pos]){
        // 오른쪽으로 n + |10 - target|만큼 회전
        ret = n + 10 - targets[pos] + digits(pos+1, offset);

        // 왼쪽으로 target - n 만큼 회전
        ret = min(ret, targets[pos] - n + digits(pos+1, (offset + targets[pos] - n) % 10));
    }else{
        // 오른쪽으로 n - target 만큼 회전
        ret = n - targets[pos] + digits(pos+1, offset);

        // 왼쪾으로 target + 10 - n 만큼 회전
        ret = min(ret, (targets[pos] + 10 - n) + digits(pos+1, (offset + targets[pos] + 10 - n) % 10));
    }
    return ret;
}

void tracking(int pos, int offset){
    if(pos == N) return;

    int n = (nums[pos] + offset) % 10;
    int turnRight, turnLeft;
    if(n < targets[pos]){
        turnRight = n + 10 - targets[pos] + digits(pos+1, offset);
        turnLeft = targets[pos] - n + digits(pos+1, (offset + targets[pos] - n) % 10);

        if(turnLeft < turnRight){
            cout << (pos+1) << " " << targets[pos] - n << endl;
            tracking(pos+1, (offset + targets[pos] - n) % 10);
        }else{
            cout << (pos+1) << " " << -(n + 10 - targets[pos]) << endl;
            tracking(pos+1, offset);
        }
    }else{
        turnRight = n - targets[pos] + digits(pos+1, offset);
        turnLeft = (targets[pos] + 10 - n) + digits(pos+1, (offset + targets[pos] + 10 - n) % 10);

        if(turnLeft < turnRight){
            cout << (pos+1) << " " << targets[pos] + 10 - n << endl;
            tracking(pos+1, (offset + targets[pos] + 10 - n) % 10);
        }else{
            cout << (pos+1) << " " << -(n - targets[pos]) << endl;
            tracking(pos+1, offset);
        }
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> N;
    string a, b;
    cin >> a;
    cin >> b;

    for(int i = 0; i < N; i++)
        nums[i] = a[i] - '0';

    for(int i = 0; i < N; i++)
        targets[i] = b[i] - '0';
    
    dp.resize(N+1, vector<int>(11, -1));
    cout << digits(0, 0) << endl;
    tracking(0, 0);
    return 0;
}