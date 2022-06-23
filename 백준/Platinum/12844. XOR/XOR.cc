#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
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

struct SegTree{
    int size;
    vector<int> lazy, tree;
    SegTree(int n){
        size = 1;
        while(size < n) size *= 2;
        size *= 2;
        lazy.resize(size);
        tree.resize(size);
    }
    void construct(){
        for(int i = size/2-1; i > 0; i--)
            tree[i] = tree[i*2] ^ tree[i*2+1];
    }
    void propagate(int node, int ns, int ne){
        if (lazy[node] != 0) {
            if (node < size/2) {
                lazy[node*2] ^= lazy[node];
                lazy[node*2+1] ^= lazy[node];
            } else
                tree[node] ^= lazy[node];
            lazy[node] = 0;
        }
    }
    void add(ll s, ll e, ll k){ add(s, e, k, 1, 0, size/2); }
    void add(ll s, ll e, ll k, ll node, ll ns, ll ne){
        propagate(node, ns, ne);

        if (e <= ns || ne <= s) return;
        if (s <= ns && ne <= e) { // 현재 노드가 구간에 완전히 포함될 때만
            lazy[node] ^= k; // 현재 노드에 lazy 값 부여하고
            propagate(node, ns, ne); // 현재 구간에 대해 lazy 값 push down
            return;
        }

        ll mid = (ns + ne)/2;
        add(s, e, k, node*2, ns, mid);
        add(s, e, k, node*2+1, mid, ne);
        tree[node] = tree[node*2] ^ tree[node*2 + 1];
    }

    ll sum(ll s, ll e){ return sum(s, e, 1, 0, size/2); }
    ll sum(ll s, ll e, ll node, ll ns, ll ne){
        // 일단 propagate
        propagate(node, ns, ne);

        if (e <= ns || ne <= s) return 0;
        if (s <= ns && ne <= e) return tree[node];
        
        ll mid = (ns + ne)/2;
        return sum(s, e, node*2, ns, mid) ^ sum(s, e, node*2+1, mid, ne);
    }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N; cin >> N;
    SegTree ST(N +1);
    for(int i = 0; i < N; i++){
        int k; cin >> k;
        ST.add(i, i+1, k);
    }
    int M; cin >> M;
    for(int i = 0; i < M; i++){
        int op, a, b, k;
        cin >> op;
        if (op == 1) {
            cin >> a >> b >> k;
            if (a > b) swap(a, b);
            ST.add(a, b + 1, k);
        } else {
            cin >> a >> b;
            if (a > b) swap(a, b);
            cout << ST.sum(a, b + 1) << endl;
        }
    }
    return 0;
}