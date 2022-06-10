#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define endl '\n'
typedef long long ll;
const ll INF = 10000000;

struct UnionFind{
    vector<ll> parent;
    vector<ll> dist;
    UnionFind(ll n){
        parent.resize(n+1, -1);
        dist.resize(n+1);
    }
    ll find(ll curr){
        if(parent[curr] < 0) return curr;

        ll root = find(parent[curr]);
        dist[curr] += dist[parent[curr]];
        return parent[curr] = root;
    }
    void merge(ll x, ll y, ll weight){
        ll rootX = find(x);
        ll rootY = find(y);
        if(rootX == rootY) return;

        dist[rootY] = dist[x] - dist[y] - weight;
        parent[rootY] = rootX;
    }
    ll getDist(ll from, ll to){
        if(find(from) != find(to)) return -INF;
        return dist[from] - dist[to];
    }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    ll N, M;
    while(true){
        cin >> N >> M;
        if(N == 0 && M == 0) break;

        UnionFind tree(N);
        for(ll i = 0; i < M; i++){
            char op; cin >> op;
            if(op == '!'){
                ll from, to, weight;
                cin >> from >> to >> weight;
                tree.merge(from, to, weight);
            }else if(op == '?'){
                ll from, to;
                cin >> from >> to;
                
                // debug(tree.find(from));
                // debug(tree.find(to));
                ll ret = tree.getDist(from, to);
                if(ret == -INF) cout << "UNKNOWN" << endl;
                else cout << ret << endl;
            }
        }
    }
    
    return 0;
}