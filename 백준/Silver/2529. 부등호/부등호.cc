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

    int K; cin >> K;
    vector<char> inequalities(K);
    vint min_res(K+1), max_res(K+1);
    for (int i = 0; i < K; i++) 
        cin >> inequalities[i];

    vint indegree(K+1);
    vector<vint> adj(K+1);
    for (int i = 0; i < K; i++) {
        if (inequalities[i] == '<') {
            adj[i+1].push_back(i);
            indegree[i]++;
        } else if (inequalities[i] == '>') {
            adj[i].push_back(i+1);
            indegree[i+1]++;
        }
    }

    priority_queue<int, vint, greater<int>> asnd_pq;
    priority_queue<int> dsnd_pq;
    for (int i = 0; i < K+1; i++)
        if (indegree[i] == 0){ 
            asnd_pq.push(i);
            dsnd_pq.push(i);
        }

    auto max_bfs = [&] (vint ind) {
        int num = 9;
        while (!asnd_pq.empty()) {
            int curr = asnd_pq.top(); asnd_pq.pop();
            max_res[curr] = num--;
            for (int next: adj[curr])
                if (--ind[next] == 0) asnd_pq.push(next);
        }
    };

    auto min_bfs = [&] (vint ind) {
        int num = K;
        while (!dsnd_pq.empty()) {
            int curr = dsnd_pq.top(); dsnd_pq.pop();
            min_res[curr] = num--;
            for (int next: adj[curr])
                if (--ind[next] == 0) dsnd_pq.push(next);
        }
    };

    max_bfs(indegree);
    min_bfs(indegree);
    
    for (int r: max_res) cout << r;
    cout << endl;
    for (int r: min_res) cout << r;
    
    return 0;
}