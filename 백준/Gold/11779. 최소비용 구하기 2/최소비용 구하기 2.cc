#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define FASTIO cin.tie(0)->sync_with_stdio(0)

#define endl '\n'
#define DEBUG
#ifdef DEBUG
#define debug(x) cout << #x << " is " << x << endl;
#define debugVect(v) do { \
    cout << #v << " is |" ; \
    for (auto i : v) cout << i << "|"; \
    cout << endl; \
} while (0)
#else
#define debug(x)
#define debugVect(v)
#endif

const int INF = 1e9;
typedef pair<int, int> pii;

int solution(int N, int M, int start, int end,
    vector<vector<pii>>& adj, vector<int>& prev)
{
    vector<int> dist(N+1, INF);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    prev.resize(N+1, 0);

    dist[start] = 0;
    pq.push({ 0, start });

    while (!pq.empty()) {
        auto [ dist_curr, curr ] = pq.top();
        pq.pop();

        if (dist_curr > dist[curr]) continue;

        for (auto& [next, cost]: adj[curr]) {
            if (dist[next] <= dist[curr] + cost) continue;

            dist[next] = dist[curr] + cost;
            pq.push({ dist[next], next });
            prev[next] = curr;
        }
    }

    return dist[end];
}

int main() {
    FASTIO;

    int N, M;
    int start, end;
    vector<vector<pii>> adj;
    vector<int> prev;

    cin >> N >> M;
    adj.resize(N + 1);
    for (int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ v, w });
    }

    cin >> start >> end;

    int ans = solution(N, M, start, end, adj, prev);

    cout << ans << endl;

    vector<int> path;
    for (int node = end; node != start; node = prev[node])
        path.push_back(node);
    path.push_back(start);

    cout << path.size() << endl;
    for (auto it = path.rbegin(); it != path.rend(); it++)
        cout << *it << " ";

    return 0;
}