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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int N, M; cin >> N >> M;

    vector<vint> adj(N);
    vint indegree(N);

    for (int i = 0; i < M; i++) {
        int A, B; cin >> A >> B;
        A--, B--;
        adj[A].push_back(B);
        indegree[B]++;
    }

    vint res;
    priority_queue<int, vint, greater<int>> pq;
    for (int i = 0; i < N; i++)
        if (indegree[i] == 0) pq.push(i);

    while (!pq.empty()) {
        int curr = pq.top(); pq.pop();
        res.push_back(curr);

        for (int next: adj[curr]) {
            if (--indegree[next] == 0) pq.push(next);
        }
    }

    for (int result: res) cout << result+1 << " ";
    return 0;
}