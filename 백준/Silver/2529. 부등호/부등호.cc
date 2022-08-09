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

    vint min_res(K+1), max_res(K+1);
    vint indegree(K+1);
    vector<vint> adj(K+1);
    for (int i = 0; i < K; i++) {
        char op; cin >> op;
        if (op == '<') {
            adj[i+1].push_back(i);
            indegree[i]++;
        } else if (op == '>') {
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

    auto bfs = [&](int num, vint& ind, auto& pq, vint &res) {
        while (!pq.empty()) {
            int curr = pq.top(); pq.pop();
            res[curr] = num--;
            for (int next: adj[curr])
                if (--ind[next] == 0) pq.push(next);
        }
    };

    // indegree를 copy해서 사용. 원본에 영향을 미치지 않음
    auto bfs_run = [&](vint ind, bool max_mode, vint& res) {
        int num = (max_mode ? 9 : K);
        if (max_mode) bfs(num, ind, asnd_pq, res);
        else          bfs(num, ind, dsnd_pq, res);
    };

    bfs_run(indegree, true, max_res);
    bfs_run(indegree, false, min_res);

    for (int r: max_res) cout << r;
    cout << endl;
    for (int r: min_res) cout << r;
    
    return 0;
}