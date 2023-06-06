#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define debug(x) cout << "[debug] " << #x << " is " << x << endl;
#define debugVec(v) do { \
    std::cout << "[Debug] ["; \
    for(int i = 0; i < ((v.size())); i++) std::cout << v[i] << "|"; \
    std::cout << "\n"; \
} while(0)
#define debugV2D(v) do { \
    std::cout << "[Debug] [\n"; \
    for(int y = 0; y < (v.size()); y++) { \
        std::cout << "  ["; \
        for(int x = 0; x < ((v[y].size())); x++) \
            std::cout << v[y][x] << "|"; \
        std::cout << "\n"; \
    } \
    std::cout << "]\n"; \
} while(0)
typedef pair<int, int> pii;
typedef vector<int> vint;
typedef vector<pii> vpii;

int N, M;
vector<vint> adj;
vint indegree;
vint res;

void bfs() {
    queue<int> q;
    for (int i = 1; i <= N; i++)
        if (indegree[i] == 0) {
            q.push(i);
            res.push_back(i);
        }

    while (!q.empty()) {
        int curr = q.front(); q.pop();

        for (int next : adj[curr]) {
            if (--indegree[next]) continue;

            q.push(next);
            res.push_back(next);
        }
    }
}

int main() {
    cin >> N >> M;
    adj = vector<vint>(N + 1);
    indegree = vint(N + 1);

    int from, to;
    for (int i = 0; i < M; i++) {
        cin >> from >> to;
        adj[from].push_back(to);
        indegree[to]++;
    }

    bfs();
    for (int r: res) cout << r << " ";
    return 0;
}