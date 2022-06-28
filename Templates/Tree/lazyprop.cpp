#include <bits/stdc++.h>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define debugVec(v) do { \
    std::cout << "[Debug] "<< #v << " is ["; \
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

struct LazyProp{
    int size, height;
    vector<int> lazy, tree;
    LazyProp(int n){
        size = 1;
        while(size < n) size *= 2;
        size *= 2;
        lazy.resize(size + 1);
        tree.resize(size + 1);

        height = log2(size/2);
    }
    /** -------- recursive version -------- **/
    void construct(){
        for(int i = size/2 -1; i > 0; i--)
            tree[i] = tree[i*2] + tree[i*2+1];
    }
    // push down lazy values in range: node ∈ [s, e)
    void propagate_(int node, int ns, int ne){
        if (lazy[node]) {
            if (node < size/2) { // if node is not leaf node
                // push down lazy values to the child nodes
                lazy[node*2] += lazy[node];
                lazy[node*2+1] += lazy[node];
            }

            // Update the interval sum of the current node
            tree[node] += lazy[node] * (ne - ns);
            lazy[node] = 0;
        }
    }
    // add value to the interval [s, e)
    void add_(int s, int e, int val){ add_(1, 0, size/2, s, e, val); }
    void add_(int node, int ns, int ne, int s, int e, int val){
        propagate_(node, ns, ne);

        if (e <= ns || ne <= s) return; // iff [ns, ne) ⊂ [s, e)
        if (s <= ns && ne <= e) {
            lazy[node] += val;
            propagate_(node, ns, ne);
            return;
        }

        int mid = (ns + ne)/2;
        add_(node*2, ns, mid, s, e, val);
        add_(node*2+1, mid, ne, s, e, val);

        // Update current node using the child nodes
        tree[node] = tree[node*2] + tree[node*2+1];
    }
    // sum of interval [s, e)
    int sum_(int s, int e){ return sum_(1, 0, size/2, s, e); }
    int sum_(int node, int ns, int ne, int s, int e){
        propagate_(node, ns, ne);

        if (e <= ns || ne <= s) return 0;
        if (s <= ns && ne <= e) return tree[node];

        int mid = (ns + ne)/2;
        return sum_(node*2, ns, mid, s, e) + sum_(node*2+1, mid, ne, s, e);
    }
    

    /** -------- non-recursive version -------- **/
    void apply(ll idx, ll val, ll range){
        if (idx < size/2) lazy[idx] += val;
        tree[idx] += val * range;
    }
    // build up in range [s, e]
    void build(ll s, ll e){
        ll l = s + size/2;
        ll r = e + size/2;
        ll range = 1;
        while(l > 1) {
            l /= 2, r /= 2;
            range *= 2;

            for (ll i = r; i >= l; i--) // do required calculation
                if (lazy[i] == 0) tree[i] = tree[i*2] + tree[i*2+1];
                // else tree[i] += lazy[i] * range; // use if needed
        }
    }
    // push down in range [s, e]
    void propagate(ll s, ll e) {
        ll l = s + size/2;
        ll r = e + size/2;
        ll range = 1 << (height-1);

        for (ll h = height; h >= 0; h--) {
            for (ll node = l >> h; node <= (r >> h); node++){ // push down from top(root)
                if (lazy[node]) {
                    apply(node*2, lazy[node], range);
                    apply(node*2+1, lazy[node], range);
                    lazy[node] = 0;
                }
            }

            range /= 2;
        }
    }
    // add val to the interval [s, e]
    void add(ll s, ll e, ll val) {
        if (val == 0) return;
        propagate(s, s);
        propagate(e, e);

        ll range = 1;
        ll l = s + size/2;
        ll r = e + size/2;
        while(l <= r){
            if (l%2) apply(l++, val, range);
            if (!(r%2)) apply(r--, val, range);
            l /= 2, r /= 2, range *= 2;
        }

        build(s, s);
        build(e, e);
    }
    // sum of interval [s, e]
    ll sum(ll s, ll e) {
        propagate(s, s);
        propagate(e, e);
        ll res = 0;
        ll l = s + size/2;
        ll r = e + size/2;
        while(l <= r) {
            if (l%2) res += tree[l++];
            if (!(r%2)) res += tree[r--];
            l /= 2, r /= 2;
        }
        return res;
    }
private:
    int log2(int n){ // same with sizeof(int) * 8 - __builtin_clz(size/2);
        int ret = 0;
        while(n > (1 << ret)) ret++;
        return ret;
    }
};

int main(){    
    // Usage example
    // problem BOJ 10999: https://www.acmicpc.net/problem/10999
    int N, M, K;
    cin >> N >> M >> K;
    LazyProp ST(N);
    
    for(int i=0; i<N; i++){
        int val; cin >> val;
        ST.tree[i + ST.size/2] = val;
    }
    ST.build(0, N);
 
    // 쿼리 처리
    for(int i=0; i<M+K; i++){
        int a, b, c, d;
        cin >> a;
        if(a == 1){
            cin >> b >> c >> d;
            ST.add(b-1, c-1, d); // update query
        }
        else{
            cin >> b >> c;
            cout << ST.sum(b-1, c-1) << endl; // sum-up query
        }
    }
    return 0;
}
