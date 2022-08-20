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
        if(v[y].empty()){ std::cout << "  []\n"; continue; } \
        std::cout << "  ["; \
        for(int x = 0; x < ((v[y].size())-1); x++) \
            std::cout << v[y][x] << "|"; \
        std::cout << v[y][(v[y].size())-1] << "]\n"; \
    } \
    std::cout << "]\n"; \
} while(0)
#define endl '\n'
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vint;
typedef vector<pii> vpii;

struct SegTree {
    int size;
    vint tree;
    SegTree (int  n) {
        for (size = 1; size < n; size *= 2);
        size *= 2;
        tree.resize(size + 1);
    }
    void insert (int idx, int val) { insert(1, 0, size/2, idx, val); }
    void insert (int node, int s, int e, int idx, int val) {
        if (idx < s || e <= idx) return; // iff idx = [s, e)
        tree[node] += val;

        if (s + 1 == e) return; // leaf
        int mid = (s + e)/2; 
        insert (node*2, s, mid, idx, val);
        insert (node*2 + 1, mid, e, idx, val);
    }
    // sum in range [qs, qe)
    int sum (int qs, int qe) { return sum(1, 0, size/2, qs, qe); }
    int sum (int node, int ns, int ne, int qs, int qe) {
        if (ne <= qs || qe <= ns) return 0; // iff [ns, ne) <= [qs, qe)
        if (qs <= ns && ne <= qe) return tree[node];

        int mid = (ns + ne)/2;
        return sum (node*2, ns, mid, qs, qe) + sum (node*2+1, mid, ne, qs, qe);
    }
};

/**
 * @brief Inverse Counting
 * 부제: 2-elements Segment Tree
 * 
 * 2-elements는 하나의 객체가 두 가지 요소 (두개의 값, 하나의 값과 입력순서 등)를 가지고 있으며
 * 그 두 가지 요소가 모두 작은 객체의 개수(LIS), 둘의 우선 순서가 뒤바뀐 쌍의 수(inversion counting) 등을 구하는 문제이다.
 * 
 * 2-elements는 보통 한 가지 요소를 사전 정렬로 처리하고, 다른 한 가지 요소를 업데이트 위치로 처리한다.
 *
 * 1. 한 가지 요소에 대해서 작은 순서로 정렬한다. 이 요소를 기준으로 아래의 과정을 진행한다.
 * 2. 나머지 한 가지 요소(첫 번째 요소의 위치)를 이용해 그 객체에 대한 원하는 값을 구한다.
 *  2-1. 객체의 위치가 i 일 때, 1 ~ i-1 중 가장 큰 LIS 값을 구하고 1을 더하면 i에 위치한 객체의 LIS를 구할 수 있다.
 *  2-2. 객체의 위치가 i 일 때, i+1 ~ n 의 요소 개수를 구하면 inversion 카운팅을 할 수 있다.
 * 3. 2에서 얻고자 하는 값 (LIS, Inversion Count)를 고려하여, 해당 위치에 필요한 값(i 위치에서의 LIS, i 위치에서의 마킹 개수)을 업데이트한다.
 */
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int N; cin >> N;
    vpii A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i].first;
        A[i].second = i;
    }

    sort(A.begin(), A.end());

    ll ans = 0;
    SegTree ST(N);
    for (auto [x, i]: A) {
        ans += ST.sum(i+1, N);
        ST.insert(i, 1);
    }
    cout << ans;
    
    return 0;
}