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
#define FASTIO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
#define endl '\n'
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vint;
typedef vector<pii> vpii;

struct SegTree {
    int size;
    vint tree;
    SegTree (int n) {
        size = 1;
        while (size < n) size <<= 1;
        size <<= 1;
        tree.resize(size + 1);
    }
    void insert(int idx, int val) {
        idx += (size >> 1);

        tree[idx] += val;
        idx >>= 1;
        while (idx > 0) {
            tree[idx] = tree[idx << 1] + tree[(idx << 1) + 1];
            idx >>= 1;
        }
    }
    int sum(int s, int e) {
        s += (size >> 1);
        e += (size >> 1);
        int ret = 0;
        while (s <= e) {
            if (s & 1) ret += tree[s++];
            if (!(e & 1)) ret += tree[e--];
            s >>= 1;
            e >>= 1;
        }
        return ret;
    }
};

vint parents;
vector<vint> children;
vint S;
vint E;
vint money;

int cnt = 0;
void dfs(int curr) {
    cnt++;
    S[curr] = cnt;

    for (int child: children[curr])
        dfs(child);
    
    E[curr] = cnt;
}

int main(){
    FASTIO;
    int N, Q; cin >> N >> Q;
    parents.resize(N + 1);
    children.resize(N + 1);
    S.resize(N + 1);
    E.resize(N + 1);
    money.resize(N + 1);

    cin >> money[1];

    for (int i = 2; i <= N; i++) {
        cin >> money[i] >> parents[i];
        children[parents[i]].push_back(i);
    }

    dfs(1);
    SegTree p_sum(N);

    for (int i = 0; i < Q; i++) {
        char query; cin >> query;
        if (query == 'p') {
            int subroot, add; cin >> subroot >> add;
            p_sum.insert(S[subroot] + 1, add);
            p_sum.insert(E[subroot] + 1, -add);
        } else {
            int node; cin >> node;
            cout << money[node] + p_sum.sum(S[1], S[node]) << endl;
        }
    }
    
    // debugVec(S);
    // debugVec(E);

    return 0;
}