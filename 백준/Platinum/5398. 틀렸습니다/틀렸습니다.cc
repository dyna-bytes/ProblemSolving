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

const int SIZE = 2002;
#define key first
#define value second

struct MaxMatching{
    int N, M;
    vector<int>A, B;
    vector<vector<int>> adj;
    vector<int> visited;
    MaxMatching (int n, int m) {
        N = n, M = m;
        A.resize(N+1, -1), B.resize(M+1, -1);
        adj.resize(N+1);
        visited.resize(N+1);
    }
    void addAdj(int from, int to) {
        adj[from].push_back(to);
    }
    bool canMatch(int a) {
        visited[a] = true;
        for (int b: adj[a]) {
            if (B[b] == -1 || !visited[B[b]] && canMatch(B[b])) {
                A[a] = b;
                B[b] = a;
                return true;
            }
        }
        return false;
    }
    int run() {
        int match = 0;
        for(int a = 0; a < N; a++){
            if (A[a] == -1){
                fill(visited.begin(), visited.end(), 0);
                if (canMatch(a)) match++;
            }
        }
        return match;
    }
};

void solve(){
    vector<vector<pii>> hmap(SIZE, vector<pii>(SIZE));
    int H, V; cin >> H >> V;
    MaxMatching Graph(H, V);

    for (int h = 0; h < H; h++) {
        int sx, sy; cin >> sx >> sy;
        string word; cin >> word;
        for (int x = 0; x < word.size(); x++)
            hmap[sy][sx + x] = {h, word[x]};
    }

    for (int v = 0; v < V; v++) {
        int sx, sy; cin >> sx >> sy;
        string word; cin >> word;
        for (int y = 0; y < word.size(); y++){
            if (hmap[sy + y][sx].value
            && (hmap[sy + y][sx].value != word[y]))
                Graph.addAdj(hmap[sy + y][sx].key, v);
        }
    }

    cout << H + V - Graph.run() << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int T; cin >> T;
    while(T--)
        solve();
    
    return 0;
}