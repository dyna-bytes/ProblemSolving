#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define debug(x) cout << "[debug] " << #x << " is " << x << endl
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define X first
#define Y second
typedef pair<int, int> pii;
typedef vector<pii> vpii;

inline int getDist(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

int B;
pii points[1001];
int p;

void solve(int& min_x, int& min_y, int& min_d) {
    sort(points, points + p, [](pii& p1, pii& p2){
        if (p1.X == p2.X) return p1.Y > p2.Y;
        return p1.X > p2.X;
    });

    min_d = INT_MAX;
    for (int here = 0; here < p; ++here) {
        int d = 0;
        for (int there = 0; there < p; ++there) {
            if (here == there) continue;
            d += getDist(points[here].X, points[here].Y, points[there].X, points[there].Y);
        }

        if (min_d >= d) {
            min_d = d;
            min_x = points[here].X;
            min_y = points[here].Y;
        }
    }
    
}

int main() {
    FASTIO;
    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        cout << "Case #" << t << ": ";
        cin >> B;
        p = 0;

        for (int i = 0; i < B; ++i) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;

            for (int x = x1; x <= x2; ++x)
                for (int y = y1; y <= y2; ++y) 
                    points[p++] = {x, y};
        }

        int res_x, res_y, res_d;
        solve(res_x, res_y, res_d);
        cout << res_x << " " << res_y << " " << res_d << endl;
    }
    return 0;
}