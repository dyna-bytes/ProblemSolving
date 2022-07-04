#include <bits/stdc++.h>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define debugVec(v) do { \
    std::cout << "[Debug] ["; \
    for(ll i = 0; i < ((v.size())-1); i++) std::cout << v[i] << "|"; \
    std::cout << v[((v.size())-1)] << "]\n"; \
} while(0)
#define debugV2D(v) do { \
    std::cout << "[Debug] [\n"; \
    for(ll y = 0; y < (v.size()); y++) { \
        std::cout << "  ["; \
        for(ll x = 0; x < ((v[y].size())-1); x++) \
            std::cout << v[y][x] << "|"; \
        std::cout << v[y][(v[y].size())-1] << "]\n"; \
    } \
    std::cout << "]\n"; \
} while(0)
#define endl '\n'
typedef long long ll;
typedef pair<ll, ll> P;

struct Tree{
    ll order = 0;
    vector<ll> parent;
    vector<vector<ll>> children;
    vector<ll> mapping, max_mapping;
    Tree(ll N){
        parent.resize(N+1);
        children.resize(N+1);
        mapping.resize(N+1);
        max_mapping.resize(N+1);
    }

    void setAdj(ll p, ll c){
        parent[c] = p;
        children[p].push_back(c);
    }

    ll preorder(ll root=1){
        mapping[root] = order++;
        max_mapping[root] = mapping[root];

        for(ll child: children[root])
            max_mapping[root] = max(max_mapping[root], preorder(child));

        return max_mapping[root];
    }


    P get_order_range(ll root){
        return {mapping[root], max_mapping[root]};
    }
    ll get_order(ll node){
        return mapping[node];
    }
};

struct LazyProp{
    ll size = 1;
    vector<ll> lazy, segtree;
    LazyProp(ll n){
        while(size < n) size *= 2;
        size *= 2;
        lazy.resize(size+1);
        segtree.resize(size+1);
    }
    void prop(ll node, ll ns, ll ne){
        if (lazy[node]) {
            if (node < size/2) {
                lazy[node*2] += lazy[node];
                lazy[node*2+1] += lazy[node];
            }

            segtree[node] += lazy[node] * (ne - ns);
            lazy[node] = 0;
        }
    }
    void add(ll s, ll e, ll val){ add(1, 0, size/2, s, e, val); }
    void add(ll node, ll ns, ll ne, ll s, ll e, ll val){
        prop(node, ns, ne);
        if (e <= ns || ne <= s) return;
        if (s <= ns && ne <= e) {
            lazy[node] += val;
            prop(node, ns, ne);
            return;
        }

        ll mid = (ns+ne)/2;
        add(node*2, ns, mid, s, e, val);
        add(node*2+1, mid, ne, s, e, val);
        segtree[node] = segtree[node*2] + segtree[node*2+1];
    }
    ll sum(ll s, ll e){ return sum(1, 0, size/2, s, e); }
    ll sum(ll node, ll ns, ll ne, ll s, ll e){
        prop(node, ns, ne);
        if (e <= ns || ne <= s) return 0;
        if (s <= ns && ne <= e) return segtree[node];

        ll mid = (ns+ne)/2;
        return sum(node*2, ns, mid, s, e) + sum(node*2+1, mid, ne, s, e);
    }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    ll N, M; cin >> N >> M;

    Tree tree(N);
    LazyProp ST(N);
    for(ll c = 1; c <= N; c++){
        ll p; cin >> p;
        if (p == -1) continue;
        tree.setAdj(p, c);
    }
    tree.preorder();

    for(ll i = 0; i < M; i++){
        ll op; cin >> op;
        if (op == 1) { //삽입 쿼리
            ll man, profit;
            cin >> man >> profit;

            P range = tree.get_order_range(man);
            ST.add(range.first, range.second+1, profit);
        } else { // 출력 쿼리
            ll man;
            cin >> man;
            ll node = tree.get_order(man);
            cout << ST.sum(node, node+1) << endl;
        }
    }
    
    return 0;
}