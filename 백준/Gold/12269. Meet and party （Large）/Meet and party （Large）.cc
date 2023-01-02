#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define debug(x) cout << "[debug] " << #x << " is " << x << endl
#define debugVec(v) do{\
    cout << "[debug] " << #v << endl;\
    for (auto e: v) cout << e << " | ";\
    cout << endl;\
}while(0)
typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<pll> vpll;
const ll INF = 1e18;
const int MAXN = 1000000; 
int B;
int N;
vpll points(MAXN);
vll x_vals(MAXN);
vll y_vals(MAXN);
vll x_psum(MAXN);
vll y_psum(MAXN);

void solve(ll& res_x, ll& res_y, ll& res_d) {
    cin >> B;
    points = {};
    x_vals = y_vals = x_psum = y_psum = {};
    for (int i = 0; i < B; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        for (int x = x1; x <= x2; ++x)
            for (int y = y1; y <= y2; ++y) 
                points.push_back({ x, y });
    }
    sort(points.begin(), points.end());
    
    N = points.size();
    x_vals.resize(N);
    for (int i = 0; i < N; ++i)
        x_vals[i] = points[i].first;
    
    sort(x_vals.begin(), x_vals.end());
    x_psum.resize(N + 1);
    for (int i = 0; i < N; ++i)
        x_psum[i + 1] = x_psum[i] + x_vals[i];
    
    y_vals.resize(N);
    for (int i = 0; i < N; ++i)
        y_vals[i] = points[i].second;
    
    sort(y_vals.begin(), y_vals.end());
    y_psum.resize(N + 1);
    for (int i = 0; i < N; ++i)
        y_psum[i + 1] = y_psum[i] + y_vals[i];
    
    res_d = INF;
    for (auto [x, y]: points) {
        ll cnt_x = lower_bound(x_vals.begin(), x_vals.end(), x) - x_vals.begin();
        ll lhs_x = x * cnt_x - x_psum[cnt_x];
        ll rhs_x = (x_psum[N] - x_psum[cnt_x]) - x * (N - cnt_x);

        ll cnt_y = lower_bound(y_vals.begin(), y_vals.end(), y) - y_vals.begin();
        ll lhs_y = y * cnt_y - y_psum[cnt_y];
        ll rhs_y = (y_psum[N] - y_psum[cnt_y]) - y * (N - cnt_y);
        
        ll dist = lhs_x + rhs_x + lhs_y + rhs_y;
        if (res_d > dist) {
            res_d = dist;
            res_x = x; 
            res_y = y;
        }
    }
}
int main() {
    FASTIO;
    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        ll res_x, res_y, res_d;
        solve(res_x, res_y, res_d);
        cout << "Case #" << t << ": ";
        cout << res_x << " " << res_y << " " << res_d << endl;
    }
    
    return 0;
}