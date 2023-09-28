#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
typedef pair<int, int> pii;
typedef vector<int> vint;
typedef vector<pii> vpii;

int N;
vpii meetings;
vint memo;

/**
 * @brief dynamic programming
 * state: n (date)
 * action: 
 * 	1. take meeting (+Pi), and move to day (n + Ti)
 * 	2. do not take meeting, and move to next day (n + 1)
 * 
 * function def.
 * f(n) = max(Pi + f(n + Ti), f(n + 1))
 */
int f(int n) {
	if (n >= N) return 0;
	if (memo[n] != -1) return memo[n];
	int& ret = memo[n];

	auto [t, p] = meetings[n];
	return ret = max(f(n + 1), 
		(n + t > N) ? 0 : p + f(n + t));
}

int main() {
	FASTIO;

	cin >> N;
	meetings = vpii(N);
	memo = vint(N, -1);
	for (auto& [t, p]: meetings) 
		cin >> t >> p;
	
	cout << f(0);
	return 0;
}
