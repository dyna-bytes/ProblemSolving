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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    // 1. 위상정렬하며 각 정점에 대한 S로부터의 최소도달시간 earlist time을 구함
    // 2. 두 정점 u, v에 대해, u에서 출발하여 v의 earlist time까지 v에 도착하는 경우
    // u에서 "출발 가능한 가장 늦은 시간" latest time을 구함
    // 3. earlist time 과 latest time이 같은 정점들이 임계경로에 속한다.
    // 다시말해, 각 정점까지의 최소도달시간이 해당 정점의 최대출발시간이라면 그 정점은 임계경로의 정점이다.
    int N, M; cin >> N >> M;

    vint indegree(N);
    vector<vpii> adj(N);
    vector<vpii> rev_adj(N);
    for (int i = 0; i < M; i++) {
        int s, e, t; cin >> s >> e >> t;
        s--, e--;
        adj[s].push_back({e, t});
        indegree[e]++;

        rev_adj[e].push_back({s, t});
    }

    int S, E; cin >> S >> E;
    S--, E--;

    vint earlist_time(N);
    queue<int> q;
    q.push(S);
    
    while (!q.empty()) {
        int curr = q.front(); q.pop();

        for (auto [next, time]: adj[curr]) {
            earlist_time[next] = max(earlist_time[next], earlist_time[curr] + time);
            if (--indegree[next] == 0) q.push(next);
        }
    }
    
    int arrival_time = earlist_time[E];
    int count = 0;
    vint visited(N); 
    q.push(E);
    while (!q.empty()) {
        int curr = q.front(); q.pop();

        for (auto [prev, time]: rev_adj[curr]) 
            if (earlist_time[curr] == time + earlist_time[prev]) {
                count++;
                if (!visited[prev]) {
                    q.push(prev);
                    visited[prev] = true;
                }
            }
        
    }

    cout << arrival_time << endl;
    cout << count;
    return 0;
}