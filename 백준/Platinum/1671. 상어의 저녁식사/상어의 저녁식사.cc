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
typedef pair<ll, ll> pll;
typedef tuple<ll, ll, ll> tlll;
typedef vector<ll> vll;

struct MaxMatching{
    int N, M;
    vll A, B;
    vector<vll> adj;
    vll visited;
    MaxMatching(int n, int m) {
        N = n, M = m;
        A.resize(N+1, -1), B.resize(M+1, -1);
        adj.resize(N+1);
        visited.resize(N+1);
    }
    void addAdj(int from, int to) { adj[from].push_back(to); }
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
    int run() {
        int match = 0;
        for (int a = 0; a < N; a++) {
            fill(visited.begin(), visited.end(), 0);
            if (canMatch(a)) match++;
        }
        return match;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int N; cin >> N;
    vector<tlll> sharks(N);
    for (int i = 0; i < N; i++) {
        int s_size, s_power, s_inteli;
        cin >> s_size >> s_power >> s_inteli;
        sharks[i] = {s_size, s_power, s_inteli};
    }

    MaxMatching Graph(N*2, N);
    auto canEat = [&](tlll& sharkA, tlll& sharkB) {
        return get<0>(sharkA) >= get<0>(sharkB)
            && get<1>(sharkA) >= get<1>(sharkB)
            && get<2>(sharkA) >= get<2>(sharkB);
    };
    auto areSame = [&](tlll& sharkA, tlll& sharkB) {
        return sharkA == sharkB;
    };

    for (int i = 0; i < N; i++) {
        for (int j = i+1; j < N; j++) {
            if (areSame(sharks[i], sharks[j])) {
                if (i < j) {
                    Graph.addAdj(i*2, j);
                    Graph.addAdj(i*2+1, j);
                } else {
                    Graph.addAdj(j*2, i);
                    Graph.addAdj(j*2+1, i);
                }
            } else if (canEat(sharks[i], sharks[j])) {
                Graph.addAdj(i*2, j);
                Graph.addAdj(i*2+1, j);                
            }  else if (canEat(sharks[j], sharks[i])) {
                Graph.addAdj(j*2, i);
                Graph.addAdj(j*2+1, i);                
            }
        }
    }   
    
    cout << N - Graph.run();
    
    return 0;
}