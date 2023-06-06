#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
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

void bfs() {
    queue<int> q;
    for (int s = 1; s <= N; s++)
        if (indegree[s] == 0) {
            q.push(s);
            cout << s << ' ';
        }

    while (!q.empty()) {
        int curr = q.front(); q.pop();

        for (int next : adj[curr]) {
            if (--indegree[next]) continue;

            q.push(next);
            cout << next << ' ';
        }
    }
}

int main() {
    FASTIO;
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
    return 0;
}