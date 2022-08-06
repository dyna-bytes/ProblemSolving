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
typedef pair<int, int> pii;
typedef vector<int> vint;
typedef vector<pii> vpii;


vint indegree;
vector<vpii> adj; // adj[Y] = {X, K}. X를 구성하는데, Y가 K개 필요함
vector<vint> dp; // dp[X][b]: 블럭 X를 구성하는데 필요한 기본부품 b의 개수를 저장
// dp[X][b] = K * dp[Y][b]: 블럭 X를 구성하는데 필요한 기본부품 b의 개수 = 중간부품 Y를 구성하는데 필요한 기본부품 b의 개수 * 중간부품 Y가 K개 필요함

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N, M; cin >> N >> M;
    indegree.resize(N);
    adj.resize(N); 
    dp.resize(N, vint(N));

    for (int i = 0; i < M; i++) {
        int X, Y, K; cin >> X >> Y >> K;
        X--, Y--;
        adj[Y].push_back({X, K});
        indegree[X]++;
    }

    queue<int> q;
    vint basics;
    for (int i = 0; i < N; i++)
        if (indegree[i] == 0){ 
            q.push(i);
            basics.push_back(i); // 기본 부품의 번호
            dp[i][i] = 1;
        }


    while (!q.empty()) {
        int curr = q.front(); q.pop();

        for (auto [next, K]: adj[curr]) {
            for (int basic: basics) 
                dp[next][basic] += K * dp[curr][basic];
            
            if (--indegree[next] == 0) q.push(next);
        }
    }

    // debugV2D(dp);
    for (int basic: basics)
        cout << basic + 1 << " " << dp[N-1][basic] << endl;
    return 0;
}