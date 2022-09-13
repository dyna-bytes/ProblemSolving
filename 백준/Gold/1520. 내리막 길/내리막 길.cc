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
typedef tuple<int, int, int> tiii;
typedef vector<int> vint;
typedef vector<pii> vpii;
typedef vector<tiii> vtiii;
const int dy[] = {-1, 1, 0, 0}, dx[] = {0, 0, -1, 1};

int Y, X;
vector<vint> heights;
vector<vint> dp;

bool inRange(int y, int x) { 
    return y >= 0 && y < Y && x >= 0 && x < X;
}

int dfs(int y, int x) {
    // terminated
    if (y == Y-1 && x == X-1) return 1;

    int& ret = dp[y][x];
    if (ret != -1) return ret;
    ret = 0;

    for (int d = 0; d < 4; d++) {
        int ny = y + dy[d], nx = x + dx[d];
        if (!inRange(ny, nx)) continue;
        if (heights[ny][nx] >= heights[y][x]) continue;
        ret += dfs(ny, nx);
    }

    return ret;
}

int bfs() {
    vector<vint> visited(Y+1, vint(X+1));
    priority_queue<tiii> pq; // {h, y, x}. h가 큰 경로부터 먼저 탐색

    visited[0][0] = 1; // 방문 횟수 저장 (dp배열과 동치)
    pq.push({heights[0][0], 0, 0});

    while (!pq.empty()) {
        auto [_, y, x] = pq.top(); pq.pop();
        for (int d = 0; d < 4; d++) {
            int ny = y + dy[d], nx = x + dx[d];
            if (!inRange(ny, nx)) continue;
            if (heights[ny][nx] >= heights[y][x]) continue;

            if (!visited[ny][nx]) 
                pq.push({heights[ny][nx], ny, nx});
            // 예제 경로 2번과 3번의 분기점에서, 큰 값을 먼저 방문해 dp배열을 채워넣고
            // 다시 합쳐지는 점에서는 나중에 오는 작은 값 방향 경로가 이미 채워진 dp값을 모두 합산 할 수 있도록 함.
            
            visited[ny][nx] += visited[y][x]; 
        }
    }

    return visited[Y-1][X-1];
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> Y >> X;
    heights.resize(Y+1, vint(X+1));
    dp.resize(Y+1, vint(X+1, -1));

    for (int y = 0; y < Y; y++)
        for (int x = 0; x < X; x++)
            cin >> heights[y][x];

    // cout << dfs(0, 0);
    cout << bfs();
    return 0;
}