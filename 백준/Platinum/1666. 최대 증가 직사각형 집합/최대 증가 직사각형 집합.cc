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
typedef tuple<int, int, int> tiii;
typedef vector<int> vint;
typedef vector<pii> vpii;
typedef vector<tiii> vtiii;

/**
 * @brief 세그먼트 트리를 이용한 DP 최적화
 * 
 * dp[i] = 0~i번 째 직사각형 중 최대 증가를 만족하는 최대 직사각형들의 개수
 * dp[i] = x[i].s (i번째 직사각형의 시작점 x좌표) > x[i'].e (i'번째 직사각형의 끝점 x좌표)
 * 를 만족하는 모든 직사각형 i'들 중 최대 dp값 + 1
 * dp[i] = 1 + max{ dp[i'] }(x[i'].e < x[i].s)
 * 
 * for (x축에 대해 스위핑)
 *   세그트리에서 max dp[0, x[i].s) 를 구함
 *   현재 dp[i]값을 계산
 *   현재 dp[i]값을 세그트리에 업데이트
 */

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

struct Rect {
    int x1, y1, x2, y2;
    Rect () { Rect(0, 0, 0, 0); }
    Rect (int _x1, int _y1, int _x2, int _y2) {
        x1 = _x1, y1 = _y1, x2 = _x2, y2 = _y2;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int N; cin >> N;
    vector<Rect> rects(N);
    int max_x = 0;
    for (int i = 0; i < N; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        rects[i] = Rect(x1, y1, x2, y2);
        max_x = max(max_x, x2);
    }

    // 모든 직사각형을 "시작점 x좌표가 증가"하는 순으로 정렬하고 번호를 붙임.
    sort(rects.begin(), rects.end(), [](Rect& r1, Rect& r2){
        if (r1.x1 == r2.x1) return r1.y1 < r2.y1;
        return r1.x1 < r2.x1;
    });

    int ans = 0;
    SegTree DP(max_x + 1); // dp values along y_axis. y축에 따른 dp값.
    priority_queue<tiii, vtiii, greater<tiii>> pq; // tuple<x2, y2, 현재 직사각형의 dp값>
    // x축을 따라 스위핑
    for (int x = 0, i = 0; x <= max_x && i < N; x++) { // i: 정렬된 i번째 직사각형
        while (i < N && rects[i].x1 < x) i++;
        if (i == N) break; // reached the end

        // 시작점 x좌표가 현재 x인 직사각형들 dp값 구함.
        for (; i < N && rects[i].x1 == x; i++) {
            int max_dp = DP.getMax(0, rects[i].y1) + 1; // dp값을 y값이 작은 값부터 큰 값으로 업데이트 해나감.
            ans = max(ans, max_dp);
            pq.push({rects[i].x2, rects[i].y2, max_dp});
        }

        // 끝점 x좌표가 현재 x인 직사각형들 dp값을 세그트리에 갱신
        while (!pq.empty()) {
            auto [x2, y2, max_dp] = pq.top();
            if (x2 != x) break; // 끝점 x좌표가 현재 x값인가?
            pq.pop();
            
            if (DP.getMax(y2, y2 + 1) < max_dp)
                DP.insert(y2, max_dp); 
        }
    }
    cout << ans;
    
    return 0;
}