#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vint;
typedef vector<ll> vll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;

#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#define endl '\n';
#define debug(x) cout << "[Debug] " << #x << " is " << x << endl;
#define _debugV1(v) for (auto it = v.begin(); it != v.end(); ++it) { cout << *it; if (next(it) != v.end()) cout << " | "; }
#define debugVec(v) do { \
    cout << "[Debug] [ "; \
    _debugV1(v); \
    cout << " ]" << endl; \
} while (0)
#define debugV2(v) do { \
    cout << "[Debug] [" << endl; \
    for (auto v1: v) { \
        cout << "  [ "; \
        _debugV1(v1); \
        cout << " ]" << endl; \
    } \
    cout << "]" << endl; \
} while (0)
#define pair_out(pair) { out << '{' << pair.first << ", " << pair.second << '}'; }
std::ostream& operator << (ostream& out, pii& pair) {
    pair_out(pair);
    return out;
}
std::ostream& operator << (ostream& out, pll& pair) {
    pair_out(pair);
    return out;
}

int N, M;
vector<vint> adj;
vint indegree;

void dfs(int curr) {
    cout << curr << ' ';
    for (int next: adj[curr]) {
        if (--indegree[next]) continue;
        dfs(next);
    }
}

int main() {
    FASTIO;
    cin >> N >> M;
    adj = vector<vint>(N + 1);
    indegree = vint(N + 1);

    int from, to;
    for (int i = 0; i < M; i++) {
        cin >> from >> to;
        adj[from].push_back(to);
        indegree[to]++;
    }

    stack<int> s;
    for (int start = 1; start <= N; start++)
        if (indegree[start] == 0)
            s.push(start);
    
    while (!s.empty()) {
        dfs(s.top());
        s.pop();
    }

    return 0;
}