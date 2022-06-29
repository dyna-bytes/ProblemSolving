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

struct LazyProp{
    int size;
    vector<int> lazy;
    vector<int> tree;
    LazyProp(int n){
        size = 1;
        while(size < n) size *= 2;
        size *= 2;
        lazy.resize(size + 1);
        tree.resize(size + 1);
    }

    void construct(){
        for(int i = size/2-1; i > 0; i--)
            tree[i] = tree[i*2] + tree[i*2+1];
    }   

    void propagate(int node, int ns, int ne){ // [ns, ne)
        if (lazy[node]) {
            if (node < size/2) { // 리프노드가 아님
                lazy[node*2] ^= 1;
                lazy[node*2+1] ^= 1;

                // 왼쪽 자식과 오른쪽 자식의 결과로 자신의 결과 갱신
                int sum = 0;
                // 만약 왼쪽 자식 전체가 반전된다면, 켜진 스위치 개수는 구간 크기 - 아직 꺼진 스위치 개수 
                if (lazy[node*2]) sum += (ne-ns)/2 - tree[node*2];
                else sum += tree[node*2]; // 아니라면 현재 켜진 스위치 개수

                if (lazy[node*2+1]) sum += (ne-ns)/2 - tree[node*2+1];
                else sum += tree[node*2+1];

                tree[node] = sum;
            }
            else tree[node] ^= 1; // 리프노드

            lazy[node] = false;
        }
    }

    // turn [s, e)
    void update(int s, int e){ update(1, 0, size/2, s, e); }
    void update(int node, int ns, int ne, int s, int e){
        propagate(node, ns, ne);

        if (e <= ns || ne <= s) return;
        if (s <= ns && ne <= e) {
            lazy[node] ^= 1; // tree노드를 직접 반전시키지 않고, lazy노드를 반전시켜서 프로퍼게이션 함수로 tree에 전파되도록 함
            propagate(node, ns, ne);
            return;
        }

        int mid = (ns + ne)/2;
        update(node*2, ns, mid, s, e);
        update(node*2+1, mid, ne, s, e);

        tree[node] = tree[node*2] + tree[node*2+1];
    }

    int query(int s, int e){ return query(1, 0, size/2, s, e); }
    int query(int node, int ns, int ne, int s, int e){
        propagate(node, ns, ne);

        if (e <= ns || ne <= s) return 0;
        if (s <= ns && ne <= e) return tree[node];

        int mid = (ns + ne)/2;
        return query(node*2, ns, mid, s, e) + query(node*2+1, mid, ne, s, e);
    }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N, M; cin >> N >> M;
    LazyProp ST(N);
    for (int i = 0; i < M; i++) {
        int op, S, E;
        cin >> op >> S >> E;
        if (op == 0) {
            // 상태 반전 쿼리
            ST.update(S, E+1);
        } else {
            cout << ST.query(S, E+1) << endl;
        }
    }
    
    return 0;
}