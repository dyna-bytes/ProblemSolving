#include <iostream>
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
	queue<pii> q; // {pos, dir}
	q.push({ sy, VER });
	q.push({ sx, HOR });
	int dist = 0;
	while (!q.empty()) {
		int size = q.size();
		for (int i = 0; i < size; i++) {
			auto [pos, dir] = q.front(); q.pop();
			if ((dir == HOR && pos == ex) || (dir == VER && pos == ey))
				return dist;
			int l, r;
			if (dir == HOR) {
				l = lower_bound(x_axis, pos);
				r = upper_bound(x_axis, pos);
				if (l == r)	continue;

				for (int j = l; j < r; j++) {
					auto [ny, nidx] = x_axis[j].second;
					if (visited[nidx][0]) continue;
					visited[nidx][0] = true;
					q.push({ ny, 1 });
				}
			}
			else
			{
				l = lower_bound(y_axis, pos);
				r = upper_bound(y_axis, pos);
				if (l == r)	continue;

				for (int j = l; j < r; j++) {
					auto [nx, nidx] = y_axis[j].second;
					if (visited[nidx][1]) continue;
					visited[nidx][1] = true;
					q.push({ nx, 0 });
				}
			}
		}
		dist++;
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