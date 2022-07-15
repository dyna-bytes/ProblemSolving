#include <bits/stdc++.h>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define debugVec(v) do { \
    std::cout << "[Debug] ["; \
    for(ll i = 0; i < ((v.size())-1); i++) std::cout << v[i] << "|"; \
    std::cout << v[((v.size())-1)] << "]\n"; \
} while(0)
#define debugV2D(v) do { \
    std::cout << "[Debug] [\n"; \
    for(ll y = 0; y < (v.size()); y++) { \
        std::cout << "  ["; \
        for(ll x = 0; x < ((v[y].size())-1); x++) \
            std::cout << v[y][x] << "|"; \
        std::cout << v[y][(v[y].size())-1] << "]\n"; \
    } \
    std::cout << "]\n"; \
} while(0)
#define endl '\n'
typedef long long ll;
typedef pair<ll, ll> P;
const ll INF = 1e9;

struct Edge {
    ll to, c, f;
    Edge* dual;
    Edge(ll to1, ll c1) {
        to = to1, c = c1, f = 0;
        dual = nullptr;
    }
    ll residual() { return c - f; }
    void addFlow(ll f1) {
        f += f1;
        dual->f -= f1;
    }
};

struct NetworkFlow {
    ll N;
    vector<vector<Edge*>> adj;
    NetworkFlow(ll n) {
        N = n;
        adj.resize(N+1);
    }
    void addAdj(ll from, ll to, ll cap) {
        Edge* e1 = new Edge(to, cap);
        Edge* e2 = new Edge(from, 0);
        e1->dual = e2;
        e2->dual = e1;
        adj[from].push_back(e1);
        adj[to].push_back(e2);
    }
    ll run(ll S, ll E) {
        vector<ll> ans;
        ll total = 0;
        while (true) {
            vector<ll> prev(N+1, -1);
            vector<Edge*> path(N+1);
            queue<ll> q;

            q.push(S);
            while (!q.empty()) {
                ll curr = q.front(); q.pop();
                if (curr == E) break;

                for (auto edge: adj[curr]) {
                    ll next = edge->to;
                    if (prev[next] != -1) continue;
                    if (edge->residual() <= 0) continue;
                    prev[next] = curr;
                    path[next] = edge;
                    q.push(next);
                    if (next == E) break;
                }
            }

            if (prev[E] == -1) break;

            ll flow = INF;
            for (ll node = E; node != S; node = prev[node])
                flow = min(flow, path[node]->residual());
            for (ll node = E; node != S; node = prev[node])
                path[node]->addFlow(flow);
            total += flow;

            for (ll node = E; node != S; node = prev[node])
                if (path[node]->residual() == 0)
                    if (abs(node - prev[node]) == N/2)
                        ans.push_back(min(node, prev[node]));
        }

        sort(ans.begin(), ans.end());
        // for (ll n: ans) cout << n << " ";
        return total;
    }
    void bfs(ll S) {
        vector<ll> ans;
        vector<ll> visited(N+1);
        queue<ll> q;
        q.push(S);
        visited[S] = true;
        while (!q.empty()) {
            int curr = q.front(); q.pop();

            for (auto edge: adj[curr]) {
                int next = edge->to;
                if (visited[next]) continue;
                if (edge->residual() <= 0) continue; 

                visited[next] = true;
                q.push(next);
            }
        }

        for (int i = 1; i <= N/2; i++)
            if (visited[i] && !visited[i+N/2]) cout << i << " ";
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    ll N, M; cin >> N >> M;
    ll S, E; cin >> S >> E;
    NetworkFlow Graph(2*N);

    for (ll i = 1; i <= N; i++) {
        ll cost; cin >> cost;
        Graph.addAdj(i, i + N, cost);
    }
    for (ll i = 1; i <= M; i++) {
        ll from, to; cin >> from >> to;
        Graph.addAdj(from + N, to, INF);
        Graph.addAdj(to + N, from, INF);
    }
    Graph.run(S, E + N);
    Graph.bfs(S);
    return 0;
}