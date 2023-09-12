#if 1
#include <iostream>
#include <vector>
#include <queue>
#include <list>
using namespace std;
typedef pair<int, int> pii;
typedef vector<int> vint;
typedef vector<pii> vpii;
#define endl '\n'
#define FUNC_LINE(f, l) "[" << f << "](" << l << ") "
#define DEBUG(x) cout << FUNC_LINE(__func__, __LINE__) << #x << " is " << x << endl;
#define FAST_IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

int N;
vint adj;
vint visited;
vint team;

int bfs(int start, int level) {
	queue<int> q;
	if (visited[start]) return -1;

	visited[start] = level;
	q.push(start);

	int loop_start = 0;
	while (!q.empty()) {
		auto curr = q.front();
		q.pop();

		auto next = adj[curr];
		if (visited[next] == level) {
			loop_start = next;
			break;
		}
		else if (visited[next])
			return -1;

		visited[next] = level;
		q.push(next);
	}

	if (loop_start) {
		q = {};
		team[loop_start] = true;
		q.push(loop_start);
		
		while (!q.empty()) {
			auto curr = q.front();
			q.pop();

			auto next = adj[curr];
			if (next == loop_start) break;

			team[next] = true;
			q.push(next);
		}
	}
	return 0;
}

int sol() {
	for (int i = 1; i <= N; ++i) {
		bfs(i, i);
	}

	int cnt = 0;
	for (int i = 1; i <= N; ++i)
		if (team[i]) ++cnt;

	return N - cnt;
}

int main() {
	FAST_IO;

	int T; cin >> T;
	while (T--) {
		cin >> N;
		adj = {};
		visited = {};
		team = {};
		adj.resize(N + 1);
		visited.resize(N + 1, 0);
		team.resize(N + 1);
		for (int i = 1; i <= N; ++i)
			cin >> adj[i];

		cout << sol() << endl;
	}

	return 0;
}
#endif