#include <bits/stdc++.h>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define debugVec(v) do { \
    std::cout << "[Debug] ["; \
    for(int i = 0; i < ((v.size())-1); i++) std::cout << v[i] << "|"; \
    std::cout << v[((v.size())-1)] << "]\n"; \
} while(0)
#define debugV2D(v) do { \
    std::cout << "[Debug] [\n"; \
    for(int y = 0; y < (v.size()); y++) { \
        if(v[y].empty()){ std::cout << "  []\n"; continue; } \
        std::cout << "  ["; \
        for(int x = 0; x < ((v[y].size())-1); x++) \
            std::cout << v[y][x] << "|"; \
        std::cout << v[y][(v[y].size())-1] << "]\n"; \
    } \
    std::cout << "]\n"; \
} while(0)
#define endl '\n'
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vint;
typedef vector<pii> vpii;

int N;
vint nums, targets;
vector<vint> dp;

int digits(int pos, int offset) {
    int& ret = dp[pos][offset];
    if (ret != -1) return ret;
    if (pos == N) return ret = 0;

    int num = (nums[pos] + offset) % 10;
    int target = targets[pos];

    // 타겟이 현재 숫자보다 오른쪽에 있다면
    if (num < target) {
        // 현재 숫자를 왼쪽으로 돌려서 타겟에 도달해보기
        ret = (target - num) + digits(pos + 1, (offset + target - num) % 10);
        // 현재 숫자를 오른쪽으로 돌려서 타겟에 도달해보기
        ret = min(ret, 10 + num - target + digits(pos + 1, offset));
    // 타겟이 현재 숫자보다 왼쪽에 있다면
    } else {
        // 현재 숫자를 왼쪽으로 돌려서 타겟에 도달해보기
        ret = 10 + target - num + digits(pos + 1, (offset + 10 + target - num) % 10);
        // 현재 숫자를 오른쪽으로 돌려서 타겟에 도달해보기
        ret = min(ret, num - target + digits(pos + 1, offset));
    }   
    return ret;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> N;
    string a, b;
    cin >> a;
    cin >> b;

    nums.resize(N);
    targets.resize(N);
    for(int i = 0; i < N; i++)
        nums[i] = a[i] - '0';

    for(int i = 0; i < N; i++)
        targets[i] = b[i] - '0';

    dp.resize(N+1, vint(11, -1));
    cout << digits(0, 0);
    return 0;
}