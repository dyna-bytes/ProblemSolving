#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define debug(x) cout << "[debug] " << #x << " is " << x << endl
const int MAX_V = 2005;
const int INF = 1e9;
/**
 * @brief Edmonds-Karp
 * 1. S -> T 증가 경로를 하나 찾는다. 증가 경로는 단순 경로이고, c(u, v) - f(u, v) > 0를 만족한다.
 * 2. 증가 경로 중 차단 간선을 찾는다. 차단 간선은 c(u, v) - f(u, v)가 최소인 간선이다.
 *  이때 min(c - f)를 F라 하자.
 * 3. 경로를 따라 F만큼의 유량을 추가한다.
 *  S -> T로 경로를 따라 f(u, v) += F
 *  역방향으로 f(v, u) -= F
 * 4. 증가 경로가 없을 때 까지 반복하며 최대 유량을 찾는다.
 */

struct Edge{
    int to, c, f; // destination, capacity, flow
    Edge* dual; // points the dual Edge of this one
    Edge(int to1 = -1, int c1 = 0){
        to = to1, c = c1, f = 0;
        dual = nullptr;
    }
    int residual(){
        return c - f;
    }
    void addFlow(int f1){
        f += f1;
        dual->f -= f1;
    }
}pool[MAX_V * MAX_V];
int p = 0;
Edge* myalloc(int to1, int c1) {
    pool[p].to = to1;
    pool[p].c = c1;
    return &pool[p++];
}

// Edmonds-Karp algorithm
struct NetworkFlow{
    int N;
    vector<Edge*> adj[MAX_V];

    void addEdge(int from, int to, int cap){
        Edge* e1 = myalloc(to, cap);
        Edge* e2 = myalloc(from, 0);
        e1->dual = e2;
        e2->dual = e1;
        adj[from].push_back(e1);
        adj[to].push_back(e2);
    }

    int run(int S, int E){
        int total = 0;
        int prev[MAX_V];
        Edge* edges[MAX_V];
        while (true) {
            memset(edges, 0, sizeof(edges));
            memset(prev, -1, sizeof(prev));  
            queue<int> q;
            q.push(S);

            while (!q.empty() && prev[E] == -1){
                int curr = q.front(); q.pop();
                if (curr == E) break; // if reached end, stop

                for (Edge* e: adj[curr]) { // e: curr-->next
                    int next = e->to;
                    // if visited next, continue
                    if (prev[next] != -1) continue;
                    if (e->residual() > 0){
                        edges[next] = e;
                        prev[next] = curr;
                        q.push(next);

                        if (next == E) break;
                    }
                }
            }

            // if there is no path to reach the end, done.
            if (prev[E] == -1) break;     

            int flow = INF; 
            // get the minimum flow through a path
            for (int node = E; node != S; node = prev[node])
                flow = min(flow, edges[node]->residual());
            // add flow to the path
            for (int node = E; node != S; node = prev[node])
                edges[node]->addFlow(flow);

            total += flow; // add up to the total flow
        }
        return total;
    }
};

int main() {
    FASTIO;
    int N, M, K;
    cin >> N >> M >> K;
    NetworkFlow graph;
    for (int n = 1; n <= N; ++n) {
        int num_job; cin >> num_job;
        while (num_job--) {
            int m; cin >> m;
            graph.addEdge(n, N + m, 1);
        }
    }
    
    int S = 0;
    for (int n = 1; n <= N; ++n)
        graph.addEdge(S, n, 1);
    
    int S_K = N + M + 2;
    for (int n = 1; n <= N; ++n)
        graph.addEdge(S_K, n, 1);

    graph.addEdge(S, S_K, K);

    int E = N + M + 1;
    for (int m = 1; m <= M; ++m)
        graph.addEdge(N + m, E, 1);

    cout << graph.run(S, E);
    return 0;
}