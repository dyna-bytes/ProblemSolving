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

struct Vert{
    int x, y1, y2;
    bool start;
    Vert(int _x, int _y1, int _y2, bool _start){
        x = _x, y1 = _y1, y2 = _y2, start = _start;
    }
};


vector<Vert> verticals;
vector<int> ylist;

struct SegTree{
    int size;
    vector<ll> count;
    vector<ll> segtree;
    SegTree(int n){
        size = 1;
        while(size < n) size *= 2;
        size *= 2;
        count.resize(size+1);
        segtree.resize(size+1);
    }

    // mark count and update segtree in range [s, e)
    void update(int s, int e, bool isStart){
        update(1, 0, ylist.size()-1, s, e, isStart);
    }
    void update(int node, int ns, int ne, int s, int e, bool isStart){
        if (ne <= s || e <= ns) return;
        if (s <= ns && ne <= e) {
            count[node] += (isStart ? 1 : -1);
        } else {
            int mid = (ns + ne)/2;
            update(node*2, ns, mid, s, e, isStart);
            update(node*2+1, mid, ne, s, e, isStart);
        }

        if (count[node]){
            segtree[node] = (ll) ylist[ne] - ylist[ns];
        } else {
            if (ns+1 == ne) segtree[node] = 0;
            else segtree[node] = segtree[node*2] + segtree[node*2+1];
        }
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int N; cin >> N;
    for (int i = 0; i < N; i++) {
        int x1, x2, y1, y2;
        cin >> x1 >> x2 >> y1 >> y2;

        verticals.push_back(Vert(x1, y1 + 1, y2 + 1, true));
        verticals.push_back(Vert(x2, y1 + 1, y2 + 1, false));

        ylist.push_back(y1 + 1);
        ylist.push_back(y2 + 1);
    }

    sort(ylist.begin(), ylist.end());
    ylist.erase(unique(ylist.begin(), ylist.end()), ylist.end());

    sort(verticals.begin(), verticals.end(), [](Vert& a, Vert& b){
        return a.x < b.x;
    });
    
    ll ans = 0;
    SegTree ST(2*N);
    for (int i = 0; i < verticals.size(); i++) {
        if (i > 0)
            ans += (verticals[i].x - verticals[i-1].x) * ST.segtree[1];
        
        int y1_idx = lower_bound(ylist.begin(), ylist.end(), verticals[i].y1) - ylist.begin();
        int y2_idx = lower_bound(ylist.begin(), ylist.end(), verticals[i].y2) - ylist.begin();

        // debug(y1_idx);
        // debug(y2_idx);
        ST.update(y1_idx, y2_idx, verticals[i].start);
        // debug(ST.segtree[1]);
    }
    cout << ans;
    return 0;
}