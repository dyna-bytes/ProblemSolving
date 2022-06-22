#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define endl '\n'
typedef long long ll;

struct SegTree{
    ll size;
    vector<ll> tree, lazy;
    SegTree(ll n){
        // size = 1;
        // while(size < n) size *= 2;
        // size *= 2;
        size = 1 << 22;
        tree.resize(size);
        lazy.resize(size);
    }
    void construct(){
        for(ll i = size/2-1; i > 0; i--)
            tree[i] = tree[i*2] + tree[i*2+1];
    }
    
    // 구간 [ns, ne)인 node의 lazy 값을 propagate
    void propagate(ll node, ll ns, ll ne){
        if (lazy[node] != 0) { // lazy 값이 존재하면 실행
            if (node < size/2) { // 리프 노드가 아니라면 자식들에게 lazy 미룸
                lazy[node*2] += lazy[node];
                lazy[node*2 + 1] += lazy[node];
            } 

            // 자신에 해당하는 lazy * 구간 값을 더함
            tree[node] += lazy[node] * (ne - ns);
            lazy[node] = 0;
        }
    }

    // 구간 [s, e)에 k를 더함
    void add(ll s, ll e, ll k){ add(s, e, k, 1, 0, size/2); }
    void add(ll s, ll e, ll k, ll node, ll ns, ll ne){
        // 일단 propagate
        propagate(node, ns, ne);

        if (e <= ns || ne <= s) return;
        if (s <= ns && ne <= e) { // 현재 노드가 구간에 완전히 포함되면
            lazy[node] += k; // lazy 값 부여 후 propagate
            propagate(node, ns, ne);
            return;
        }

        ll mid = (ns + ne)/2;
        add(s, e, k, node*2, ns, mid);
        add(s, e, k, node*2+1, mid, ne);
        tree[node] = tree[node*2] + tree[node*2 + 1];
    }

    // 구간 [s, e)의 합
    ll sum(ll s, ll e){ return sum(s, e, 1, 0, size/2); }
    ll sum(ll s, ll e, ll node, ll ns, ll ne){
        // 일단 propagate
        propagate(node, ns, ne);

        if (e <= ns || ne <= s) return 0;
        if (s <= ns && ne <= e) return tree[node];
        
        ll mid = (ns + ne)/2;
        return sum(s, e, node*2, ns, mid) + sum(s, e, node*2+1, mid, ne);
    }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    ll N, M, K; cin >> N >> M >> K;
    SegTree ST(1 << 21 + 1);
    for(ll i = 0; i < N; i++)
        cin >> ST.tree[i + ST.size/2];
    ST.construct();

    for(ll i = 0; i < M+K; i++){
        ll a, b, c, d;
        cin >> a;
        if (a == 1) {
            cin >> b >> c >> d;
            ST.add(b-1, c, d);
        } else {
            cin >> b >> c;
            cout << ST.sum(b-1, c) << endl;
        }
    }
    
    return 0;
}