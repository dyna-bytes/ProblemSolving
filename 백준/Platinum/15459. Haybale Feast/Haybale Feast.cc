#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define endl '\n'
typedef long long ll;
typedef pair<ll, ll> Pair;

Pair operator+(Pair& p1, Pair& p2){
    return {p1.first + p2.first, p1.second + p2.second};
}

Pair operator+=(Pair& p1, Pair& p2){
    return p1 = p1 + p2;
}

struct UnionFind{
    vector<Pair> parent; // {parent, flavor}
    UnionFind(ll n, vector<ll> flavors){
        parent.resize(n + 1);
        
        for(ll i = 0; i < n; i++)
            parent[i] = {-1, flavors[i]};
    }
    // find root
    ll find(ll n){
        if(parent[n].first < 0) return n;
        return parent[n].first = find(parent[n].first); 
    }
    void merge(ll a, ll b){
        a = find(a);
        b = find(b);
        if(a == b) return;

        parent[a] += parent[b];
        parent[b].first = a;
    }
    ll getFlavorSum(ll n){
        return parent[find(n)].second;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    ll N, M;
    cin >> N >> M;

    vector<ll> flavors(N), spiciness(N);
    vector<Pair> index(N);

    for(ll i = 0; i < N; i++){
        cin >> flavors[i] >> spiciness[i];
        index[i] = {spiciness[i], i};
    }

    UnionFind uf(N, flavors);
    sort(index.begin(), index.end());

    for(Pair pair: index){
        ll index = pair.second;
        ll left = (index - 1 >= 0)? index - 1 : 0;
        ll right = (index + 1 < N)? index + 1 : N-1;

        if(spiciness[left] <= spiciness[index])
            uf.merge(left, index);
        if(spiciness[index] >= spiciness[right])
            uf.merge(index, right);
        if(uf.getFlavorSum(index) >= M){
            cout << spiciness[index];
            break;
        }
    }
    return 0;
}