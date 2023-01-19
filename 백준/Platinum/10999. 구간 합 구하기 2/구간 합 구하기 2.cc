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

struct LazyProp{
    ll size;
    vector<ll> lazy, tree;
    LazyProp(ll n){
        size = 1;
        while(size < n) size *= 2;
        size *= 2;
        lazy.resize(size + 1);
        tree.resize(size + 1);
    }

    void calc(ll idx, ll range){
        if (lazy[idx] == 0) tree[idx] = tree[idx*2] + tree[idx*2+1];
        // else tree[idx] += lazy[idx] * range;
    }

    void apply(ll idx, ll val, ll range){
        tree[idx] += val * range;
        if (idx < size/2) lazy[idx] += val;
    }

    void build(ll l, ll r){
        ll range = 2;
        for (l += size/2, r += (size/2 - 1); l > 1; range *= 2) {
            l /= 2, r /= 2;
            for (ll i = r; i >= l; i--) calc(i, range);
        }
    }

    void push(ll l, ll r) {
        ll h = sizeof(int) * 8 - __builtin_clz(size/2);
        ll range = 1 << (h-1);
        for (l += size/2, r += (size/2 - 1); h > 0; h--, range /= 2){
            for (ll i = l >> h; i <= (r >> h); i++){
                if (lazy[i]) {
                    apply(i*2, lazy[i], range);
                    apply(i*2+1, lazy[i], range);
                    lazy[i] = 0;
                }
            }
        }
    }

    void modify(ll l, ll r, ll val) {
        if (val == 0) return;
        push(l, l+1);
        push(r-1, r);
        // debug("After push");
        // debugVec(lazy);
        // debugVec(tree);

        ll L = l, R = r, range = 1;
        for (l += size/2, r += size/2; l < r; l /= 2, r /= 2, range *= 2) {
            if (l&1) apply(l++, val, range);
            if (r&1) apply(--r, val, range);
        }

        // debug("After apply");
        // debugVec(lazy);
        // debugVec(tree);

        build(L, L+1);
        build(R-1, R);

        // debug("After build");
        // debugVec(lazy);
        // debugVec(tree);
    }

    ll query(ll l, ll r) {
        push(l, l+1);
        push(r-1, r);
        ll res = 0;
        for (l += size/2, r += size/2; l < r; l /= 2, r /= 2) {
            if (l&1) res += tree[l++];
            if (r&1) res += tree[--r];
        }
        return res;
    }

private:
    ll log2(ll n){
        ll ret = 0;
        while(n > (1 << ret)) ret++;
        return ret;
    }
};

int main(){    
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    ll N, M, K;
    cin >> N >> M >> K;
    LazyProp ST(N);
    
    for(ll i=0; i<N; i++){
        ll val; cin >> val;
        // ST.modify(i, i+1, val);
        ST.tree[i + ST.size/2] = val;
    }
    ST.build(0, N);

    // debugVec(ST.lazy);
    // debugVec(ST.tree);
 
    // 쿼리 처리
    for(ll i=0; i<M+K; i++){
        ll a, b, c, d;
        cin >> a;
        if(a == 1){
            cin >> b >> c >> d;
            ST.modify(b-1, c, d);
        }
        else{
            cin >> b >> c;
            cout << ST.query(b-1, c) << endl;
        }
    }
    return 0;
}