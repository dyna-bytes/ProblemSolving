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

const int MAX_X = 100'001;
const int MAX_K = 18;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N;
    cin >> N;
    vector<int> energies(N+1);
    for (int i = 1; i <= N; i++)
        cin >> energies[i];

    vector<vector<P>> adj(N+1);
    for (int i = 0; i < N-1; i++) {
        int from, to, len;
        cin >> from >> to >> len;
        
        adj[from].push_back({to, len});
        adj[to].push_back({from, len});
    }

    vector<vector<int>> parent(MAX_X, vector<int>(MAX_K));
    vector<vector<int>> dist(MAX_X, vector<int>(MAX_K));

    // bfs
    vector<int> visited(N+1);
    queue<P> q;

    visited[1] = true;
    q.push({1, 0});
    while (!q.empty()) {
        auto [curr, len] = q.front(); q.pop();
        // dist[curr][0] = len;

        for (auto [next, nextlen]: adj[curr]) {
            if (visited[next]) continue;

            visited[next] = true;
            parent[next][0] = curr;
            dist[next][0] = nextlen;
            q.push({next, nextlen});
        }
    }

    for (int k = 0; k < MAX_K-1; k++)
        for (int x = 1; x <= N; x++) {
            parent[x][k+1] = parent[ parent[x][k] ][k];
            dist[x][k+1] = dist[x][k] + dist[ parent[x][k] ][k];
        }
    
    // for (int i = 1; i <= N; i++) {
    //     cout << endl;
    //     for (int k = 0; k < MAX_K-1; k++)
    //         cout << dist[i][k] << " ";
    // }
    
    for (int i = 1; i <= N; i++) {
        int x = i;
        int energy = energies[x];
        for (int k = MAX_K-1; k >= 0; k--) 
            if (x == 1) break;
            else if (energy - dist[x][k] >= 0) {
                if (parent[x][k]) {
                    energy -= dist[x][k];
                    x = parent[x][k];
                } 
            } 
            
        cout << x << endl;
    }

    return 0;
}