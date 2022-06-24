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
const int INF = 1e9+1;

struct BFS01{
    int N;
    vector<vector<P>> adj;
    vector<int> dist;
    BFS01(const int& n){
        N = n;
        adj.resize(N+1);
        dist.resize(N+1, INF);
    }
    void setAdj(const int& from, const int& to, const int& weight){
        adj[from].emplace_back(to, weight);
    }
    int getDist(int target){ return dist[target]; }
    void run(const int& S){
        fill(dist.begin(), dist.end(), INF);
        deque<int> dq;

        dist[S] = 0;
        dq.push_back(S);

        while(!dq.empty()){
            const int curr = dq.front(); dq.pop_front();

            for(const P& p: adj[curr]){
                const int next = p.first, weight = p.second;

                if (dist[next] <= dist[curr] + weight) continue;
                dist[next] = dist[curr] + weight;

                if (weight) dq.emplace_back(next);
                else dq.emplace_front(next);
            }
        }
    }
};

void solve(){
    int N, K, M; cin >> N >> K >> M;
    int V = N + 4*K;
    BFS01 Graph(V);
    vector<int> last(N);
    iota(last.begin(), last.end(), 0); // 벡터를 0부터 시작해서 연속적인 값으로 채움

    for(int k = 0; k < K; k++){
        int from, to; cin >> from >> to;
        from--; to--;

        int horizon_from = N + 4*k;
        int horizon_to = N + 4*k + 2;

        Graph.setAdj(last[from], horizon_from, 0);
        Graph.setAdj(last[to], horizon_to, 0);
        Graph.setAdj(horizon_from, horizon_from + 1, 1);
        Graph.setAdj(horizon_from, horizon_to + 1, 0);
        Graph.setAdj(horizon_to, horizon_from + 1, 0);
        Graph.setAdj(horizon_to, horizon_to + 1, 1);

        last[from] = horizon_from + 1;
        last[to] = horizon_to + 1;
    }

    vector<vector<int>> query(N);
    for(int i = 0; i < M; i++){
        int from, to; cin >> from >> to;
        from--; to--;
        query[from].push_back(to);
    }

    int ans = 0;
    for(int from = 0; from < N; from++){
        Graph.run(from);

        for(int to: query[from])
            ans += (Graph.getDist(last[to]) == INF? -1 : Graph.getDist(last[to]));
    }

    cout << ans << endl;
};

int main(int argc, char** argv){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int T, test_case;

    cin >> T;
    for(test_case = 0; test_case  < T; test_case++){
        
        cout << "Case #" << test_case+1 << endl;
        solve();
    }

    return 0;
}