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

struct UnionFind {
    vint parent;
    UnionFind(int n) {
        parent.resize(n, -1);
    }
    
    int find(int curr) {
        if (parent[curr] < 0) return curr;
        return parent[curr] = find(parent[curr]);
    }

    bool merge(int from, int to) {
        from = find(from);
        to = find(to);

        if (from == to) return false;

        if (abs(parent[from]) > abs(parent[to])) swap(from, to);
        parent[to] += parent[from];
        parent[from] = to;
        return true;
    }
};

int solve(int N, int Q, vpii& query) {
    UnionFind disjoint_sets(N);

    for (int i = 0; i < Q; i++) {
        auto [from, to] = query[i];
        if (disjoint_sets.merge(from, to) == false) return i+1;
    }

    return 0;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int N, Q; cin >> N >> Q;
    vpii query(Q);
    for (int i = 0; i < Q; i++) 
        cin >> query[i].first >> query[i].second;
    
    cout << solve(N, Q, query);
    return 0;
}