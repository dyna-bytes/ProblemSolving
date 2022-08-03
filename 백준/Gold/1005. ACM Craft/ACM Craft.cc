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

int N, K;
int dist;
vint time_(1000);
vint result(1000);
vint indegree(1000);
vector<vint> adj(1000);

void solve(){
    cin >> N >> K;
    time_.clear();
    result.clear();
    indegree.clear();
    adj.clear();

    time_.resize(N, 0);
    result.resize(N, 0);
    indegree.resize(N, 0);
    adj.resize(N);
    
    for (int i = 0; i < N; i++)
        cin >> time_[i];

    for (int i = 0; i < K; i++) {
        int X, Y;
        cin >> X >> Y;
        X--, Y--;
        adj[X].push_back(Y);
        indegree[Y]++;
    }

    cin >> dist;
    dist--;
    
    queue<int> q;
    for (int i = 0; i < N; i++)
        if (indegree[i] == 0) q.push(i);

    while (indegree[dist] > 0) {
        int curr = q.front(); q.pop();

        for (int next: adj[curr]) {
            result[next] = max(result[next], result[curr] + time_[curr]);
            if (--indegree[next] == 0) q.push(next);
        }
    }
    cout << result[dist] + time_[dist] << endl;
};

int main(int argc, char** argv){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int T, test_case;

    cin >> T;
    for(test_case = 0; test_case  < T; test_case++){
        solve();
    }

    return 0;
}