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

struct SegTree {
    int size;
    vint segtree;
    SegTree (int n) {
        size = 1;
        while (size < n) size *= 2;
        size *= 2;
        segtree.resize(size + 1);
    }
    void insert (int idx, int val) { insert(1, 0, size/2, idx, val); }
    void insert (int node, int ns, int ne, int idx, int val) {
        if (idx < ns || idx >= ne) return; // idx = [s, e)
        segtree[node] += val;

        if (ns + 1 == ne) return;
        int mid = (ns + ne)/2;
        insert (node*2, ns, mid, idx, val);
        insert (node*2+1, mid, ne, idx, val);
    }
    int sum (int qs, int qe) { return sum(1, 0, size/2, qs, qe); }
    int sum (int node, int ns, int ne, int qs, int qe) {
        if (ne <= qs || qe <= ns) return 0;
        if (qs <= ns && ne <= qe) return segtree[node];

        int mid = (ns + ne)/2;
        return sum (node*2, ns, mid, qs, qe)
             + sum (node*2+1, mid, ne, qs, qe);
    }
};

#define INSERT 1
#define PRINT 2
#define DIRECTION 3

vector<vint> children;
vint visited;
vint S, E;
int cnt = 0;

void dfs (int curr) {
    visited[curr] = true;
    cnt++;

    S[curr] = cnt;
    for (int next: children[curr]) {
        if (visited[next]) continue;
        dfs(next);
    }
    E[curr] = cnt;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N, Q; cin >> N >> Q;

    children.resize(N+1);
    visited.resize(N+1);
    S.resize(N+1);
    E.resize(N+1);

    for (int i = 1; i <= N; i++) {
        int parent; cin >> parent;
        if (parent == -1) continue;
        children[parent].push_back(i);
    }

    dfs(1);
    SegTree Upward(cnt+1);
    SegTree Downward(cnt+1);
    bool isDownward = true;

    for (int i = 0; i < Q; i++) {
        int query, a, w;
        cin >> query;
        if (query == INSERT) {
            cin >> a >> w;
            if (isDownward) {
                Downward.insert(S[a], w);
                Downward.insert(E[a] + 1, -w);
            } else 
                Upward.insert(S[a], w);
        } else if (query == PRINT) {
            cin >> a;
            cout << Downward.sum(S[1], S[a] + 1) + Upward.sum(S[a], E[a] + 1) << endl;
        } else if (query == DIRECTION) 
            isDownward ^= 1;
    }
    return 0;
}