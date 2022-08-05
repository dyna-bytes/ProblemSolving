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
typedef pair<int, int> pii;
typedef vector<int> vint;
typedef vector<pii> vpii;

vint strahler(1000);
vpii num_of_strahler(1000); 
vint indegree(1000);
vector<vint> adj(1000);

void solve() {
    int K, M, P;
    cin >> K >> M >> P;
    strahler.clear();
    num_of_strahler.clear();
    indegree.clear();
    adj.clear();

    strahler.resize(M);
    num_of_strahler.resize(M);
    indegree.resize(M);
    adj.resize(M);

    for (int i = 0; i < P; i++) {
        int A, B; cin >> A >> B;
        A--, B--;
        adj[A].push_back(B);
        indegree[B]++;
    }

    queue<int> q;
    for (int i = 0; i < M; i++)
        if (indegree[i] == 0) {
            strahler[i] = 1;
            num_of_strahler[i] = {strahler[i], 1};
            q.push(i);
        }

    while (!q.empty()) {
        int curr = q.front(); q.pop();
        auto [curr_max_strahler, curr_num] = num_of_strahler[curr];
        if (curr_num == 1) strahler[curr] = curr_max_strahler;
        else strahler[curr] = curr_max_strahler + 1;

        for (int next: adj[curr]) {
            auto [max_strahler, num] = num_of_strahler[next];

            if (max_strahler < strahler[curr]) 
                num_of_strahler[next] = {strahler[curr], 1};
            else if (max_strahler == strahler[curr])
                num_of_strahler[next].second++;
            
            if (--indegree[next] == 0) q.push(next);
        }
    }
    cout << K << " " << strahler[M-1] << endl;
    // debugVec(strahler);
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int T; cin >> T;
    while (T--) solve();
    return 0;
}