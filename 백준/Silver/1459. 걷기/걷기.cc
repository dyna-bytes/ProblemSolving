#include <stdio.h>
#define MIN(x, y) ( (x) < (y) ? (x) : (y) )
typedef long long ll;

ll solve(ll X, ll Y, ll W, ll S) {
	ll ret = 0;
	if (X == 0 || Y == 0) {
		if (W <= S) return (X + Y)*W;
		
		if ((X + Y)%2) return (X + Y - 1)*S + W;
		else return (X + Y)*S;
	}

	if (2*W <= S) {
		ret = (X + Y)*W;
	} else {
		ll min_xy = MIN(X, Y);
		ret = min_xy * S + solve(X - min_xy, Y - min_xy, W, S);
	}
	return ret;
}

int main() {
	ll X, Y;
	ll W, S;
	scanf("%lld %lld %lld %lld", &X, &Y, &W, &S);
	printf("%lld", solve(X, Y, W, S));
	return 0;
}
