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
#define startl '\n'
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vint;
typedef vector<pii> vpii;


struct SegTree {
    int size;
    vint segtree;
    SegTree (int n) {
        size = 1;
        while (size < n) size *= 2;
        size *= 2;
        segtree.resize(size+1);
    }
    void insert (int idx, int val) {
        idx += size/2;
        
        segtree[idx] = max(segtree[idx], val);
        idx /= 2;
        while (idx > 0) {
            segtree[idx] = max(segtree[idx*2], segtree[idx*2+1]);
            idx /= 2;
        }
    }
    int getMax (int qs, int qe) { return getMax(1, 0, size/2, qs, qe); }
    int getMax (int node, int ns, int ne, int qs, int qe) {
        if (ne <= qs || qe <= ns) return 0;
        if (qs <= ns && ne <= qe) return segtree[node];

        int mid = (ns + ne)/2;
        return max( getMax (node*2, ns, mid, qs, qe), 
                    getMax (node*2+1, mid, ne, qs, qe) );
    }
};

struct Point {
    int x, y, idx;
    bool start;
    Point () { Point(0, 0, false, 0); }
    Point (int _x, int _y, bool _start, int _idx) {
        x = _x, y = _y, start = _start, idx = _idx;
    }
};

/**
 * @brief 세그먼트 트리를 이용한 DP 최적화
 * 
 * dp[i] = 0~i번 째 직사각형 중 최대 증가를 만족하는 최대 직사각형들의 개수
 * dp[i] = x[i].s (i번째 직사각형의 시작점 x좌표) > x[i'].e (i'번째 직사각형의 끝점 x좌표)
 * 를 만족하는 모든 직사각형 i'들 중 최대 dp값 + 1
 * dp[i] = 1 + max{ dp[i'] }(x[i'].e < x[i].s && y[i'] < y[i])
 * 
 * for (x축을 따라 점들을 스위핑)
 *   만약 시작점이라면 
 *     y값이 커지는 순으로 세그트리에서 max dp[0, 현재 점의 y) 를 구함
 *     현재 점 i의 dp[i]값을 계산
 *   만약 끝점이라면
 *     현재 점 i의 dp[i]값을 세그트리에 업데이트
 */

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int N; cin >> N;
    int max_y = 0;
    vector<Point> points(2*N);
    for (int i = 0; i < N; i++) {
        int sx, sy, ex, ey;
        cin >> sx >> sy >> ex >> ey;
        points[i*2] = {sx, sy, true, i};
        points[i*2+1] = {ex, ey, false, i};
        max_y = max(max_y, ey);
    }

    // 모든 점들을 x좌표 순으로, 만약 x좌표가 같다면 시작점이 앞으로 오도록 정렬함.
    sort(points.begin(), points.end(), [](Point& p1, Point& p2){
        if (p1.x == p2.x) return p1.start > p2.start;
        return p1.x < p2.x;
    });

    vint dp(N);
    SegTree DP(max_y + 1); // y좌표에 따른 dp값.
    
    // x축을 따라 스위핑
    for (Point point: points) {
        if (point.start) dp[point.idx] = DP.getMax(0, point.y) + 1;
        else DP.insert(point.y, dp[point.idx]);
    }

    cout << *max_element(dp.begin(), dp.end());
    return 0;
}