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
typedef tuple<int, int, int, int> tiiii;
typedef vector<int> vint;
typedef vector<pii> vpii;
typedef vector<tiiii> vtiiii;

#define LEFT    0
#define EGG     1
#define RIGHT   2
#define TYPE    get<0>
#define X       get<1>
#define Y       get<2>
#define Y2      get<3>

struct SegTree {
    int size;
    vint tree;
    SegTree (int n) {
        size = 1;
        while (size < n) size *= 2;
        size *= 2;
        tree.resize(size + 1);
    }
    void insert (int idx, int val=1) {
        idx += size/2;

        tree[idx] += val;
        idx /= 2;
        while (idx > 0) {
            tree[idx] = tree[idx*2] + tree[idx*2+1];
            idx /= 2;
        }
    }
    int sum (int s, int e) {
        int l = s + size/2;
        int r = e + size/2;
        int ret = 0;
        while (l <= r) {
            if (l % 2) ret += tree[l++];
            if (!(r % 2)) ret += tree[r--];
            l /= 2;
            r /= 2;
        }
        return ret;
    }
};

void solve () {
    int max_y = -1;
    int N, Q; cin >> N >> Q;
    vtiiii eggs_and_lines;
    for (int i = 0; i < N; i++) {
        int x, y; cin >> x >> y;
        eggs_and_lines.push_back({EGG, x, y, 0});
        max_y = max(max_y, y);
    }   

    for (int i = 0; i < Q; i++) {
        int l, r, b, t; cin >> l >> r >> b >> t;
        eggs_and_lines.push_back({LEFT, l, b, t});
        eggs_and_lines.push_back({RIGHT, r, b, t});
        max_y = max(max_y, t);
    }

    // x축을 따라 스위핑한다. 왼쪽 수직선, 계란, 오른쪽 수직선의 우선순위로 스위핑 대상을 지정
    sort(eggs_and_lines.begin(), eggs_and_lines.end(), [] (tiiii& t1, tiiii& t2) {
        if (X(t1) == X(t2)) return TYPE(t1) < TYPE(t2);
        return X(t1) < X(t2);
    });

    int total_egg_count = 0;
    SegTree ST(max_y + 1);  
    // x축을 따라 스위핑하며
    // 1. 왼쪽 수직선과 평행한 영역에 존재하는 점들을 모두 빼주고,
    // 2. 왼쪽 수직선과 오른쪽 수직선 사이에 점들을 박아넣고, 
    // 3. 방금 박은 점들을 포함하여 오른쪽 수직선과 평행한 영역에 존재하는 점들을 모두 다시 센다.
    for (tiiii& egg_or_line: eggs_and_lines) {
        auto [type, x, y, y2] = egg_or_line;

        if (type == EGG) {
            ST.insert(y, 1);
        } else {
            int egg_count = ST.sum(y, y2); // 높이 [b, t] 내의 계란 개수
            if (type == LEFT) total_egg_count -= egg_count; // 이전에 존재하던 점
            if (type == RIGHT) total_egg_count += egg_count;// 이전에 존재하던 점 + 새로 추가된 점
            // (이전에 존재하던 점 + 새로 추가된 점) - 이전에 존재하던 점
            // == 새로 추가된 점
        }
    }
    cout << total_egg_count << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int T; cin >> T;
    while (T--)
        solve();
    
    return 0;
}