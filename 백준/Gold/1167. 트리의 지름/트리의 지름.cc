#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;
typedef vector<int> vint;
typedef vector<pii> vpii;

vector<vpii> adj;
vint visited;

pii dfs(int curr) {
	int farthest = curr;
	int ret = 0;
	visited[curr] = true;

	for (auto [next, weight] : adj[curr]) {
		if (visited[next]) continue;

		pii searched = dfs(next);
		if (ret < weight + searched.first) {
			ret = weight + searched.first;
			farthest = searched.second;
		}
	}
	return { ret, farthest };
}

int main() {
	int V; cin >> V;
	adj.resize(V + 1);
	visited.resize(V + 1);

	for (int i = 0; i < V; i++) {
		int from; cin >> from;
		int to, weight;
		while (true) {
			cin >> to;
			if (to == -1) break;
			cin >> weight;

			adj[from].push_back({ to, weight });
		}
	}

	pii ret1 = dfs(1);
	visited.clear(); visited.resize(V + 1);

	pii ret2 = dfs(ret1.second);
	cout << ret2.first;
	return 0;
}