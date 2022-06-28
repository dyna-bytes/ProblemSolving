#include <bits/stdc++.h>
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
    vector<int> tree;
    SegTree(int n){
        size = 1;
        while(size < n) size *= 2;
        size *= 2;
        tree.resize(size + 1);
    }
    void construct(){
        for(int i = size/2-1; i > 0; i--)
            tree[i] = tree[i*2] + tree[i*2+1];
    }
    /** -------- non-recursive version -------- **/
    void insert(int idx, int val){
        idx += size/2; // add correction term to index
        
        tree[idx] += val;
        idx /= 2;
        while(idx > 0){
            tree[idx] = tree[idx*2] + tree[idx*2+1];
            idx /= 2;
        }
    }
    // sum in range of [s, e]
    int sum(int s, int e){
        int l = s + size/2;
        int r = e + size/2;
        int ret = 0;
        while(l <= r){
            if (l % 2) ret += tree[l++];
            if (!(r % 2)) ret += tree[r--];
            l /= 2;
            r /= 2;
        }
        return ret;
    }
    

    /** -------- recursive version -------- **/
    void insert_(int idx, int val){ insert_(1, 0, size/2, idx, val); }
    void insert_(int node, int s, int e, int idx, int val){
        if (idx < s || e <= idx) return; // iff idx ∈ [s, e)
        tree[node] += val;

        if (s+1 == e) return; // iff idx ∈ [s, e)
        int mid = (s + e)/2;
        insert_(node*2, s, mid, idx, val);
        insert_(node*2+1, mid, e, idx, val);
    }
    // sum in range of [s, e)
    int sum_(int s, int e){ return sum_(1, 0, size/2, s, e); }
    int sum_(int node, int ns, int ne, int s, int e){
        if (ne <= s || e <= ns) return 0; // iff [ns, ne) ⊂ [s, e)
        if (s <= ns && ne <= e) return tree[node];

        int mid = (ns + ne)/2;
        return sum_(node*2, ns, mid, s, e) + sum_(node*2+1, mid, ne, s, e);
    }
};

int main(){
    // Usage example
    // problem BOJ 2042: https://www.acmicpc.net/problem/2042
    int N, M, K;
    cin >> N >> M >> K;
    SegTree ST(N);
    for(int i = 0; i < N; i++){
        cin >> ST.tree[i + ST.size/2];
    }
    ST.construct();

    for(int i = 0; i < M + K; i++){
        int op, a, b;
        cin >> op >> a >> b;
        a--; b--;
        if(op == 1){
            b++;
            int diff = b - ST.tree[a + ST.size/2];
            ST.insert_(a, diff);
        }else
            cout << ST.sum_(a, b+1) << endl;
    }

    debugVec(ST.tree);
    return 0;
}
