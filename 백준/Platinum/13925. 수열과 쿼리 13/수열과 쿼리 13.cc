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
const ll MOD = 1e9 + 7;

struct LazyProp{
    ll size = 1;
    vector<ll> lazy_a, lazy_b, segtree;
    LazyProp(ll n){
        while(size < n) size *= 2;
        size *= 2;
        lazy_a.resize(size+1, 1);
        lazy_b.resize(size+1);
        segtree.resize(size+1);
    }

    // segtree[node] = a*segtree[node] + b
    // default: a=1, b=0
    // add: a=1, b=val
    // mul: a=val, b=val
    // set: a=0, b=val
    void prop(ll node, ll ns, ll ne){
        if (lazy_a[node] != 1 || lazy_b[node] != 0) {
            if (node < size/2) {
                // 곱을 누적해서 내려보냄
                lazy_a[node*2] = (lazy_a[node*2] * lazy_a[node])%MOD; // a[2n] = a[2n] * a[n]
                lazy_a[node*2+1] = (lazy_a[node*2+1] * lazy_a[node])%MOD;

                // 아랫단에 +b를 푸쉬하려면 윗단에서 이미 a배 곱해진 것을 보정하여 푸쉬다운해야함
                lazy_b[node*2] = (lazy_b[node*2] * lazy_a[node] + lazy_b[node])%MOD; // b[2n] = b[2n] * a[n] + b[n]
                lazy_b[node*2+1] = (lazy_b[node*2+1] * lazy_a[node] + lazy_b[node])%MOD;
            }

            segtree[node] = (lazy_a[node]*segtree[node] + lazy_b[node] * (ne-ns))%MOD;
            lazy_a[node] = 1;
            lazy_b[node] = 0;
        }
    }
    
    void update(ll s, ll e, ll val, ll mode){ update(1, 0, size/2, s, e, val, mode); }
    void update(ll node, ll ns, ll ne, ll s, ll e, ll val, ll mode){
        prop(node, ns, ne);
        if (e <= ns || ne <= s) return;
        if (s <= ns && ne <= e) {
            if (mode == 1) {
                (lazy_b[node] += val)%=MOD;
            } else if (mode == 2) {
                (lazy_a[node] *= val)%=MOD;
                (lazy_b[node] *= val)%=MOD;
            } else if (mode == 3) {
                lazy_a[node] = 0;
                lazy_b[node] = val;
            }
            prop(node, ns, ne);
            return;
        }
        ll mid = (ne+ns)/2;
        update(node*2, ns, mid, s, e, val, mode);
        update(node*2+1, mid, ne, s, e, val, mode);

        segtree[node] = (segtree[node*2] + segtree[node*2+1])%MOD;
    }
    ll query(ll s, ll e){ return query(1, 0, size/2, s, e); }
    ll query(ll node, ll ns, ll ne, ll s, ll e){
        prop(node, ns, ne);
        if (e <= ns || ne <= s) return 0;
        if (s <= ns && ne <= e) return segtree[node];
        ll mid = (ne+ns)/2;
        return (query(node*2, ns, mid, s, e) + query(node*2+1, mid, ne, s, e))%MOD;
    }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll N; cin >> N;
    LazyProp ST(N+1);
    for(ll i = 0; i < N; i++){
        ll v; cin >> v;
        ST.update(i, i+1, v, 1);
    }

    ll M; cin >> M;
    for(ll i = 0; i < M; i++){
        ll op, x, y, v;
        cin >> op;
        if (op == 1) { // 구간합 쿼리
            cin >> x >> y >> v;
            ST.update(x-1, y, v, op);
        } 
        if (op == 2) { // 구간곱 쿼리 
            cin >> x >> y >> v;
            ST.update(x-1, y, v, op);
        }
        if (op == 3) { // 구간갱신 쿼리
            cin >> x >> y >> v;
            ST.update(x-1, y, v, op);
        }
        if (op == 4) { // 구간 내의 합 쿼리
            cin >> x >> y;
            cout << ST.query(x-1, y) << endl;
        }
    }
    return 0;
}