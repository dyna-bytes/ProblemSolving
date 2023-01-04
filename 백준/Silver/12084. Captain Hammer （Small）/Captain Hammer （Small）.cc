#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
const double G = 9.8;
const double PI = atan(1) * 4;

double solve() {
    double V, D; cin >> V >> D;
    if (V == 0) return 0;
    double form = G * D / (V * V);
    // sin(x) = sqrt(1 - sqrt(1 - sin^2(2x))). 사인 2배각 공식
    double sin = sqrt( (1 - sqrt(max(0.0, 1 - pow(form, 2)))) / 2 );
    double radian = asin( sin );
    double theta = radian * 180 / PI;
    return theta;
}
int main() {
    FASTIO;
    cout << fixed;
    cout.precision(7);
    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        cout << "Case #" << t << ": ";
        cout << solve() << endl;
    }
    return 0;
}