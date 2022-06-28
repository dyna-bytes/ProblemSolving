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
    }

    void apply(ll idx, ll val, ll range){
        tree[idx] += val * range;
        if (idx < size/2) lazy[idx] += val;
    }

    // build in range [s, e]
    void build(ll s, ll e){
        ll l = s + size/2;
        ll r = e + size/2;
        ll range = 1;
        while(l > 1) {
            l /= 2, r /= 2;
            range *= 2;

            for (ll i = r; i >= l; i--) calc(i, range);
        }
    }

    // push in range [s, e]
    void push(ll s, ll e) {
        ll h = log2(size/2); //sizeof(int) * 8 - __builtin_clz(size/2);
        ll range = 1 << (h-1);
        ll l = s + size/2;
        ll r = e + size/2;
        while(h > 0){
            for (ll i = l >> h; i <= (r >> h); i++){
                if (lazy[i]) {
                    apply(i*2, lazy[i], range);
                    apply(i*2+1, lazy[i], range);
                    lazy[i] = 0;
                }
            }

            h--; range /= 2;
        }
    }

    // update val to the range [s, e]
    void modify(ll s, ll e, ll val) {
        if (val == 0) return;
        push(s, s);
        push(e, e);

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

    ll query(ll s, ll e) {
        push(s, s);
        push(e, e);
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
        ST.tree[i + ST.size/2] = val;
    }
    ST.build(0, N-1);
 
    // 쿼리 처리
    for(ll i=0; i<M+K; i++){
        ll a, b, c, d;
        cin >> a;
        if(a == 2){
            cin >> b >> c >> d;
            ST.modify(b-1, c-1, d);
        }
        else{
            cin >> b >> c;
            cout << ST.query(b-1, c-1) << endl;
        }
    }
    return 0;
}