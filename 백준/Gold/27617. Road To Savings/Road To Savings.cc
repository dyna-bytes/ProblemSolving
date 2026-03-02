/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define fastio() ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
typedef pair<int, int> pii;
const int INF = 1e9;

int dijkstra(int S, int E, int N, 
    vector<vector<pii>>& adj,
    int min_dist = 0) 
{
    vector<int> dist(N + 1, INF);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    
    dist[S] = 0;
    pq.push({ 0, S });
    
    int cnt = 0;
    while (pq.size()) {
        auto [dsum, curr] = pq.top(); pq.pop();
        
        if (curr == E && min_dist && dsum == min_dist)
            cnt++;
        
        for (auto& [next, cost]: adj[curr]) {
            if (dist[next] < dsum + cost) continue;
            
            dist[next] = dsum + cost;
            pq.push({ dist[next], next });
        }
    }
    
    if (min_dist) return cnt * dist[E];
    return dist[E];
}

int main()
{
    fastio();
    int N, M, A, B;
    cin >> N >> M >> A >> B;
    vector<vector<pii>> adj;
    adj.resize(N + 1);
    
    int total_len = 0;
    for (int i = 0; i < M; i++) {
        int u, v, l;
        cin >> u >> v >> l;
        adj[u].push_back({ v, l });
        adj[v].push_back({ u, l });
        total_len += l;
    }
    
    int min_dist = dijkstra(A, B, N, adj);
    cout << total_len - dijkstra(A, B, N, adj, min_dist) << endl;
    
    return 0;
}