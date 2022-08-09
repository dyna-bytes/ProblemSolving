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

    int N; cin >> N;

    unordered_set<int> nodes;
    vint indegree(26);
    vector<vint> adj(26);

    string prev = "";
    for (int i = 0; i < N; i++) {
        string curr; cin >> curr;

        bool same = true;
        for (int i = 0; i < curr.size(); i++) {
            nodes.insert(curr[i]);

            // 앞의 철자들은 모두 동일하고 최초로 u, v의 자리에서 알파벳이 달라진 다면
            // 알파벳 u가 v보다 사전 순으로 앞선다는 뜻임.
            if (i < prev.size() && curr[i] != prev[i]) {
                int u = curr[i] - 'a';
                int v = prev[i] - 'a';

                // u가 v보다 사전 순으로 앞선다면 v->u 간선을 만듦
                adj[v].push_back(u);
                indegree[u]++;
                same = false;
                break;
            }
        }

        // 올바르지 않은 입력을 처리
        if (same && prev.size() > curr.size()) {
            cout << "!";
            return 0;
        }

        prev = curr;
    }

    queue<int> q;
    for (int node: nodes) {
        int u = node - 'a';
        if (indegree[u] == 0) q.push(u);
    }

    vint res(nodes.size());
    auto bfs = [&]() {
        for (int i = 0; i < nodes.size(); i++) {
            if (q.size() > 1) return -2;
            if (q.empty())    return -1;

            int curr = q.front(); q.pop();
            res[i] = curr + 'a';
            for (int next: adj[curr])
                if (--indegree[next] == 0) q.push(next);    
        }
        return 0;
    };

    int error = bfs();
    if (error == -2)        cout << "?";
    else if (error == -1)   cout << "!";
    else for (char c: res)  cout << c;
    
    return 0;
}