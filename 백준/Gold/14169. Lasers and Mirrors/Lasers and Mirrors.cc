#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <tuple>
#include <cassert>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define debug(x) cout << "[debug] " << #x << " is " << x << endl;
#define debugVec(v) do{\
	cout << "[debug] " << #v << endl;\
	for (auto e: v) cout << e << " | ";\
	cout << endl;\
}while(0);
typedef long long ll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef tuple<pii, int, int> tpii;
typedef vector<int> vint;
typedef vector<pii> vpii;
const int INF = 1e9 + 1;
#define HOR 0 // horizontal
#define VER 1 // vertical
#define Y first
#define X second

int N;
vector<pair<int, pii>> y_axis; // {y, {x, idx}}
vector<pair<int, pii>> x_axis; // {x, {y, idx}}
vector<vint> visited;

int lower_bound(vector<pair<int, pii>>& axis, int key) {
	int s = 0, e = N;
	while (s < e) {
		int mid = (s + e) / 2;
		if (axis[mid].first < key) s = mid + 1;
		else e = mid;
	}
	return s;
}
int upper_bound(vector<pair<int, pii>>& axis, int key) {
	int s = 0, e = N;
	while (s < e) {
		int mid = (s + e) / 2;
		if (axis[mid].first <= key) s = mid + 1;
		else e = mid;
	}
	return s;
}

int bfs(int sy, int sx, int ey, int ex) {
	queue<tiii> q; // {pos, dir, mirrors}
	q.push({ sy, HOR, 0 });
	q.push({ sx, VER, 0 });
	while (!q.empty()) {
		auto [curr, dir, mirrors] = q.front(); // {현재의 x 또는 y 좌표, 직전에 빛이 쏘아진 방향, 튕긴 거울 수}
		q.pop();

		int y = -1, x = -1;
		if (dir == VER) x = curr;
		else y = curr;

		if (dir == HOR && y == ey) return mirrors;
		if (dir == VER && x == ex) return mirrors;

		// 만약 수직으로 거울에 들어왔다면
		if (dir == VER) {
			// 수평한 방향의 근처 거울을 찾음
			int l_idx = lower_bound(x_axis, x);
			int r_idx = upper_bound(x_axis, x);
			if (l_idx == r_idx) continue;

			for (int idx = l_idx; idx < r_idx; idx++) {
				auto [_, next] = x_axis[idx];
				auto [ny, nidx] = next;
				if (visited[nidx][HOR]) continue;
				visited[nidx][HOR] = true;
				q.push({ ny, HOR, mirrors + 1 });
			}
		}
		else {
			int l_idx = lower_bound(y_axis, y);
			int r_idx = upper_bound(y_axis, y);
			if (l_idx == r_idx) continue;

			for (int idx = l_idx; idx < r_idx; idx++) {
				auto [_, next] = y_axis[idx];
				auto [nx, nidx] = next;
				if (visited[nidx][VER]) continue;
				visited[nidx][VER] = true;
				q.push({ nx, VER, mirrors + 1 });
			}
		}
	}

	return -1;
}

int main() {
	FASTIO;
	cin >> N;
	y_axis.resize(N);
	x_axis.resize(N);
	visited.resize(N + 2, vint(2));

	int sx, sy, ex, ey; cin >> sx >> sy >> ex >> ey;


	for (int i = 0; i < N; i++) {
		int x, y; cin >> x >> y;

		y_axis[i] = { y, {x, i} };
		x_axis[i] = { x, {y, i} };
	}

	sort(y_axis.begin(), y_axis.end());
	sort(x_axis.begin(), x_axis.end());

	cout << bfs(sy, sx, ey, ex);
	return 0;
}
