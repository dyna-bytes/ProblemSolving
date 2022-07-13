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

// 단순 구간합 세그트리. 근데 이분 탐색을 곁들인
struct SegTree{
    int size = 1;
    vector<int> segtree;
    SegTree(int n) {
        while(size < n) size *= 2;
        size *= 2;
        segtree.resize(size+1);
    }
    // A[i]에 해당하는 리프노드에 A[i]가 추가되면 +1, A[i]가 제거되면 -1을 한다.
    // 무식하게 K개의 A[0], A[1], ... A[K-1] 값들을 몽땅 세그트리 리프노드에 박아놓고 (이걸 하기 위해 세그트리의 크기가 무지막지한건 덤)
    // 세그트리의 조상 노드들에는 [ns, ne) 범위에 속한 A[]의 개수를 저장한다.
    // 어떤 리프 노드의 범위가 [ns, ns+1) 일 때, 해당 범위 앞으로 [0, ns)의 범위에 (K+1)/2 - 1개의
    // A[] 값들이 존재한다면, ns의 값이 곧 (K+1)/2번째 A[]의 값이 될 것이다.

    // idx = A[], val = +-1
    void update(int idx, int val) { update(1, 0, size/2, idx, val); }
    void update(int node, int ns, int ne, int idx, int val) {
        if (idx < ns || ne <= idx) return;
        segtree[node] += val;

        if (ns + 1 == ne) return;
        int mid = (ns+ne)/2;
        update(node*2, ns, mid, idx, val);
        update(node*2+1, mid, ne, idx, val);
    }
    int query(int cnt) { return query(1, 0, size/2, cnt); }
    int query(int node, int ns, int ne, int cnt) {
        if (ns + 1 == ne) return ns; 

        int mid = (ns + ne)/2;
        if (segtree[node*2] >= cnt) return query(node*2, ns, mid, cnt);
        else return query(node*2+1, mid, ne, cnt - segtree[node*2]);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int N, K; cin >> N >> K;
    SegTree ST(65535 + 1);
    vector<int> A(N);
    for(int i = 0; i < N; i++) cin >> A[i];

    for(int i = 0; i < K; i++)
        ST.update(A[i], 1);
    
    ll sum = ST.query((K+1)/2);
    // debug(sum);
    for(int i = K; i < N; i++) {
        ST.update(A[i-K], -1);
        ST.update(A[i], 1);
        sum += ST.query((K+1)/2);
        // debug(sum);
    }
    cout << sum;
    
    return 0;
}