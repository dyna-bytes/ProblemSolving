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

int listSize;

struct MaxMatching{
    int N, M;
    vector<int> A, B;
    vector<vector<int>> adj;
    vector<bool> visited;
    MaxMatching(int n, int m) {
        N = n, M = m;
        A.resize(N, -1), B.resize(M, -1);
        adj.resize(N);
        visited.resize(N);
    }
    bool canMatch(int a) {
        if (visited[a]) return false;
        visited[a] = true;

        for (int b: adj[a]) {
            if (B[b] == -1 || canMatch(B[b])) {
                A[a] = b;
                B[b] = a;
                return true;
            }
        }
        return false;
    }
    vector<int> run(vector<int>& evens) {
        vector<int> ret;
        for (int b: adj[0]) {
            fill(A.begin(), A.end(), -1);
            fill(B.begin(), B.end(), -1);
            
            A[0] = b;
            B[b] = 0;
            int flow = 1;
            for (int a = 1; a < A.size(); a++) {
                fill(visited.begin(), visited.end(), 0);
                visited[0] = true;
                if (canMatch(a)) flow++;
            }
            if (flow == A.size()) ret.push_back(evens[b]);
        }

        if (ret.empty()) return {-1};
        else {
            sort(ret.begin(), ret.end());
            return ret;
        }
    }
};

vector<bool> isPrime(1000, true);
void era() {
    for (int i = 3; i < 2000; i += 2) {
        if (!isPrime[i/2]) continue;
        for (int j = i*i; j < 2000; j += i*2)
            isPrime[j/2] = false;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N; cin >> N;
    bool isFirstNumOdd = false;
    vector<int> odds, evens;
    for (int i = 0; i < N; i++) {
        int inp; cin >> inp;
        (inp % 2 ? odds : evens).push_back(inp);

        if (i == 0 && inp % 2) isFirstNumOdd = true;
    }

    if (odds.size() != evens.size()) {
        cout << -1; return 0;
    }

    era();
    if (!isFirstNumOdd) odds.swap(evens);
    MaxMatching Graph(odds.size(), evens.size()); // 사실 odds.size == evens.size 똑같음

    for (int a = 0; a < odds.size(); a++) 
        for (int b = 0; b < evens.size(); b++)
            if (isPrime[(odds[a] + evens[b])/2])
                Graph.adj[a].push_back(b);
    
    auto ret = Graph.run(evens);
    for (int i = 0; i < ret.size(); i++)
        cout << ret[i] << " ";

    return 0;
}