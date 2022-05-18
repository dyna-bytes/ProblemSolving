#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <unordered_set>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define endl '\n'
typedef long long ll;

struct UnionFind{
    vector<ll> parent;
    UnionFind(ll n){
        parent.resize(n+1, -1);
    }
    ll find(ll n){
        if(parent[n] < 0) return n;
        return parent[n] = find(parent[n]);
    }
    void merge(ll u, ll v){
        u = find(u);
        v = find(v);
        if(u == v) return;

        if(abs(parent[u]) < abs(parent[v])) swap(u, v);
        parent[u] += parent[v];
        parent[v] = u;
    }
    ll getSize(ll n){
        return abs(parent[find(n)]);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    ll N, M, Q;
    cin >> N >> M >> Q;

    UnionFind uf(N);
    vector<vector<ll>> adj(M + 1, vector<ll>(2)); // one base index
    vector<ll> query(Q);
    unordered_set<ll> querySet;

    for(ll m = 1; m <= M; m++){
        cin >> adj[m][0] >> adj[m][1];
    }

    for(ll i = 0; i < Q; i++){
        cin >> query[i];
        querySet.insert(query[i]);
    }

    for(ll m = 1; m <= M; m++){
        if(querySet.find(m) != querySet.end()) continue;

        uf.merge(adj[m][0], adj[m][1]);
    }

    ll ret = 0;
    for(ll i = Q - 1; i >= 0; i--){
        ll m = query[i];

        ll u = adj[m][0], v = adj[m][1];
        if(uf.find(u) == uf.find(v)) continue;

        ret += (uf.getSize(u) * uf.getSize(v));
        uf.merge(u, v);
    }
    cout << ret;

    return 0;
}