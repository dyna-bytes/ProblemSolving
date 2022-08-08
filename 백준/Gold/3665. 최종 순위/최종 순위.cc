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
        for(int x = 0; x < (((int)v[y].size())-1); x++) \
            std::cout << v[y][x] << "|"; \
        std::cout << v[y][((int)v[y].size())-1] << "]\n"; \
    } \
    std::cout << "]\n"; \
} while(0)
#define endl '\n'
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vint;
typedef vector<pii> vpii;

vint original(500);
set<pii> renewal;
vint res(500);
vint indegree(500);
vector<vint> adj(500);

void init (int n) {
    original.clear();
    renewal.clear();
    res.clear();
    indegree.clear();
    adj.clear();

    original.resize(n);
    res.resize(n);
    indegree.resize(n);
    adj.resize(n);
}

void solve () {
    int N; cin >> N;
    init(N);

    vint IDXtoRNK(N); // Index to Rank. ItoR[idx] = rank. idx 순위의 팀 번호 = rank
    vint RNKtoIDX(N); // Rank to Index. RtoI[rank] = index. 번호가 rank인 팀의 순위 = idx

    for (int idx = 0; idx < N; idx++) {
        int rank; cin >> rank; rank--;

        IDXtoRNK[idx] = rank;
        RNKtoIDX[rank] = idx;
    }

    int M; cin >> M;
    vector<vint> swapped(N, vint(N));

    for (int i = 0; i < M; i++) {
        int rank_a, rank_b; cin >> rank_a >> rank_b; rank_a--, rank_b--;

        // IDX가 작을 수록 더 높은 순위
        // 항상 a팀의 순위가 b팀의 순위보다 더 낮도록 유지함.
        if (RNKtoIDX[rank_a] > RNKtoIDX[rank_b]) swap(rank_a, rank_b);

        adj[rank_b].push_back(rank_a);
        indegree[rank_a]++;
        swapped[rank_a][rank_b] = true;
    }

    for (int rank_i = 0; rank_i < N; rank_i++)
     for (int rank_j = 0; rank_j < N; rank_j++) {
        if (rank_i == rank_j) continue;
        if (RNKtoIDX[rank_i] < RNKtoIDX[rank_j] && !swapped[rank_i][rank_j]) {
            adj[rank_i].push_back(rank_j);
            indegree[rank_j]++;
        }
     }

    queue<int> q;
    for (int i = 0; i < N; i++)
        if (indegree[i] == 0) q.push(i);

    auto bfs = [&]() {
        for (int i = 0; i < N; i++) {
            if (q.size() > 1) return -2;
            if (q.empty()) return -1;

            int curr = q.front(); q.pop();
            res[i] = curr;

            for (int next: adj[curr])
                if (--indegree[next] == 0) q.push(next);
        }
        return 0;
    };
    
    int error = bfs();
    if (error == -2) cout << "?" << endl;
    else if (error == -1) cout << "IMPOSSIBLE" << endl;
    else {
        for (int i = 0; i < N; i++) cout << res[i]+1 << " ";
        cout << endl;
    }
    // debugV2D(adj);
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int T; cin >> T;
    while (T--) solve();
    return 0;
}