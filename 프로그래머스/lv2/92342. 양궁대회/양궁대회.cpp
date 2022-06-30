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
        std::cout << "  ["; \
        for(int x = 0; x < ((v[y].size())-1); x++) \
            std::cout << v[y][x] << "|"; \
        std::cout << v[y][(v[y].size())-1] << "]\n"; \
    } \
    std::cout << "]\n"; \
} while(0)
#define endl '\n'
typedef long long ll;
typedef pair<int, int> P;
const int INF = 1e9;

int N;
vector<int> infos;
vector<vector<int>> dp;
// k: 현재 보고 있는 과녁의 순서, n: 남은 화살 개수
int f(int k, int n){ // f(k, n): 상대와의 점수 차이 
    if (k == 11) return 0;
    if (n == 0) {
        int sum = 0;
        for (int i = k; i < 11; i++)
            if (infos[i]) sum += (10-i);
        return -sum;
    }
    
    int& ret = dp[k][n];
    if (ret != -INF) return ret;

    // 일단 져보기
    ret = f(k+1, n) - (infos[k]? (10-k) : 0);
    // 이겨보기
    if (n >= infos[k]+1)
        ret = max(ret, f(k+1, n-infos[k]-1) + (10-k));
    return ret;
}

void tracking(int k, int n, vector<int>& ans){
    if (k == 10 || n == 0){ 
        for(int i = k; i < 10; i++) ans[i] = 0;
        ans[10] = n; // 마지막에는 남은 화살을 다 소진해야 함
        return;
    }

    int lose = f(k+1, n) - (infos[k]? (10-k) : 0);
    int win = (n >= infos[k]+1)? f(k+1, n-infos[k]-1)+(10-k) : -INF;
    
    if (lose == win && win != -INF) {
        ans[k] = 0;
        tracking(k+1, n, ans);
        vector<int> low_hits(11);

        for(int i = 10; i >= 0; i--)
            low_hits[i] = ans[i];

        ans[k] = infos[k]+1;
        tracking(k+1, n-infos[k]-1, ans);

        bool choose_first = true;
        for(int i = 10; i >= 0; i--) {
            if (ans[i] && low_hits[i]) continue;
            if (ans[i]) {
                choose_first = false;
                break;
            } 
            if (low_hits[i]) {
                break;
            }
        }

        if (choose_first) {
            ans[k] = 0;
            tracking(k+1, n, ans);
        }
    } else if (lose > win) { 
        ans[k] = 0;
        tracking(k+1, n, ans);
    } else { 
        ans[k] = (infos[k]+1);
        tracking(k+1, n-infos[k]-1, ans);
    }    
}

// 라이언이 이길려면 어피치보다 한 발 씩만 더 맞히면 됨
vector<int> solution(int n, vector<int> info) {
    N = n;
    infos = info;
    dp.clear();
    dp.resize(12, vector<int>(100, -INF));

    int res = f(0, N);
    if (res <= 0) return {-1};

    vector<int> answer(11); // ans[i]: 10-i 점을 맞힌 화살 개수
    tracking(0, N, answer);
    return answer;
}