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

const int MAX_X = 100000;

void bfs(int S, int E) {
    auto inRange = [&](int x){ return x >= 0 && x <= MAX_X; };

    vint prev(MAX_X + 1);
    vint visited(MAX_X + 1);

    queue<pii> q;
    visited[S] = true;
    q.push({S, 0});

    int ret = MAX_X;
    while (!q.empty()) {
        auto [x, t] = q.front(); q.pop();

        if (x == E) {
            ret = min(ret, t);
            continue;
        }

        if (inRange(x+1) && !visited[x+1]) {
            visited[x+1] = true;
            prev[x+1] = x;
            q.push({x+1, t+1});
        }

        if (inRange(x-1) && !visited[x-1]) {
            visited[x-1] = true;
            prev[x-1] = x;
            q.push({x-1, t+1});
        }

        if (x && inRange(x*2) && !visited[x*2]) {
            visited[x*2] = true;
            prev[x*2] = x;
            q.push({x*2, t+1});
        }
    }

    cout << ret << endl;

    vint tracking;
    for (int x = E; x != S; x = prev[x])
        tracking.push_back(x);
    tracking.push_back(S);

    reverse(tracking.begin(), tracking.end());
    for (int x: tracking) cout << x << " ";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N, K; cin >> N >> K;
    bfs(N, K);
    return 0;
}