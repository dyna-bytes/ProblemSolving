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
#define Y first 
#define X second
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vint;
typedef vector<ll> vll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;
const ll OFFSET = 2e5;
const ll MOD = 1e9 + 7;

struct SegTree {
    int size;
    vll tree;
    SegTree (int n) {
        size = 1;
        while (size < n) size *= 2;
        size *= 2;
        tree.resize(size + 1);
    }
    void construct () {
        for (int i = size/2 - 1; i > 0; i--)
            tree[i] = tree[i*2] + tree[i*2 + 1];
    }
    void insert (int idx, ll val) {
        idx += size/2;

        tree[idx] += val;
        idx /= 2;
        while (idx > 0) {
            tree[idx] = tree[idx*2] + tree[idx*2 + 1];
            idx /= 2;
        }
    }
    ll sum (int s, int e) { // sum in range [s, e]
        int l = s + size/2;
        int r = e + size/2;
        ll ret = 0;
        while (l <= r) {
            if (l % 2) ret += tree[l++];
            if (!(r % 2)) ret += tree[r--];
            l /= 2;
            r /= 2;
        }
        return ret;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int N; cin >> N;

    ll x_max = -1;
    vpll stars(N);
    for (int i = 0; i < N; i++) {
        ll x, y; cin >> x >> y;
        stars[i] = {y + OFFSET, x + OFFSET};
        x_max = max(x_max, x + OFFSET);
    }

    // 별들을 y좌표가 커지는 순으로, y좌표가 같다면 x좌표가 커지는 순으로 정렬함.
    sort(stars.begin(), stars.end(), [] (pll& p1, pll& p2) {
        if (p1.Y == p2.Y) return p1.X < p2.X;
        return p1.Y < p2.Y;
    });

    SegTree ST(x_max + 1);
    for (pll star: stars) // 모든 별들의 x좌표에 대응하는 리프노드를 마킹해둠.
        ST.tree[star.X + ST.size/2]++;
    ST.construct();

    ll ans = 0;
    int last = -1;
    // x축에 대해 왼쪽에서 오른쪽으로 한 줄 씩 스위핑하며, y축에 대해 위로 올라감.
    for (int i = 0; i < N; i++) {
        if (i > last) // 별들은 y좌표가 커지는 순으로 정렬되어 있음.
            for (int j = i; j < N; j++) {
                // 높이가 같고 x좌표가 더 큰 별들을 지워감.
                if (stars[i].Y == stars[j].Y) {
                    last = j;
                    ST.insert(stars[j].X, -1);
                }
                else break;
            } // 이러면 현재 별보다 y좌표가 높은 별들만 세그트리에 남게 됨.

        if (stars[i].X == 0 || stars[i].X == x_max) continue;

        ll left_stars = ST.sum(0, stars[i].X - 1);      // 현재 별보다 왼쪽에 있는 별들의 수
        ll right_stars = ST.sum(stars[i].X + 1, x_max); // 현재 별보다 오른쪽에 있는 별들의 수

        // debug(left_stars);
        // debug(right_stars);
        (ans += (left_stars * right_stars)) %= MOD;
    }
    cout << ans;
    
    return 0;
}