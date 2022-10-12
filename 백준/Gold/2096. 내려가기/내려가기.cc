#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vint;

int N;
vector<vint> dp_max(2, vint(3));
vector<vint> dp_min(2, vint(3));

int main() {
	cin >> N;
	
	int x0, x1, x2;
	cin >> x0 >> x1 >> x2;
	dp_max[0] = dp_min[0] = {x0, x1, x2};
	
	for (int y = 1; y < N; y++) {
		cin >> x0 >> x1 >> x2;
		dp_max[1][0] = x0 + max({dp_max[0][0], dp_max[0][1]});
		dp_max[1][1] = x1 + max({dp_max[0][0], dp_max[0][1], dp_max[0][2]});
		dp_max[1][2] = x2 + max({dp_max[0][1], dp_max[0][2]});
		
		dp_max[0] = dp_max[1];
		
		
		dp_min[1][0] = x0 + min({dp_min[0][0], dp_min[0][1]});
		dp_min[1][1] = x1 + min({dp_min[0][0], dp_min[0][1], dp_min[0][2]});
		dp_min[1][2] = x2 + min({dp_min[0][1], dp_min[0][2]});
		
		dp_min[0] = dp_min[1];
	}
	
	cout << max({dp_max[0][0], dp_max[0][1], dp_max[0][2]}) << " ";
	cout << min({dp_min[0][0], dp_min[0][1], dp_min[0][2]});
	
	return 0;
}
