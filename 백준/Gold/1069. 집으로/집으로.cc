#include <bits/stdc++.h>
#define FASTIO cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(0)
#define endl '\n'
using namespace std;
typedef long double ldouble;

ldouble jump(ldouble Z, ldouble D, ldouble T) {
    if (Z > D){
        ldouble walk = Z;
        ldouble simple = T + jump(Z-D, D, T);
        if (Z < 2*D) {
            ldouble triangle = 2*T;
            return min({walk, simple, triangle});
        }
        return min(walk, simple);
    }

    ldouble walk = Z;
    ldouble turnback = T + (D - Z);
    ldouble triangle = 2*T;
    return min({walk, turnback, triangle});
}

int main() {
    ldouble X, Y, D, T;
    ldouble Z;
    cin >> X >> Y >> D >> T;
    Z = [](ldouble X, ldouble Y){
        return sqrt(X*X + Y*Y);
    }(X, Y);

    cout << fixed;
    cout.precision(11);
    cout << jump(Z, D, T) << endl;
    return 0;
}