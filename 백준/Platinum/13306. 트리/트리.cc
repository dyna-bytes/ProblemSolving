#include <bits/stdc++.h>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define debugVec(v) do { \
    std::cout << "[Debug] ["; \
    for(int i = 0; i < ((v.size())-1); i++) std::cout << v[i] << "|"; \
    std::cout << v[((v.size())-1)] << "]\n"; \
} while(0)
#define debugV2D(v) do { \
    std::cout << "[Debug] [\n"; \
    for(int y = 0; y < (v.size()); y++) { \
        if(v[y].empty()){ std::cout << "  []\n"; continue; } \
        std::cout << "  ["; \
        for(int x = 0; x < ((v[y].size())-1); x++) \
            std::cout << v[y][x] << "|"; \
        std::cout << v[y][(v[y].size())-1] << "]\n"; \
    } \
    std::cout << "]\n"; \
} while(0)
#define endl '\n'
typedef long long ll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef vector<int> vint;
typedef vector<pii> vpii;
typedef vector<tiii> vtiii;

int N;
vint parent;
int root = 1;

// union-find
vint p;
int find(int curr) {
    if (p[curr] == -1) return curr;
    return p[curr] = find(p[curr]);
}

/**
 * @brief 집합을 분리해가며 두 노드가 한 분리집합 안에 있는지 확인하는 문제
 * 
 * @details 역순으로 분리집합들을 합쳐가며 두 노드가 한 분리집합 안에 있는지 확인한다.
 * 
 * 결국에는 모든 간선을 제거함 => 최종상태: 크기가 1인 분리집합 N개
 * 처음에는 모든 간선이 연결됨 => 최초상태: 크기가 N인 분리집합 1개
 * 
 * 최종상태에서 최초상태로 역순으로 쿼리를 진행한다.
 * 두 노드를 끊는 쿼리가 등장하기 이전에는 두 노드가 연결된 상태이었으므로,
 * "끊는 쿼리"가 등장할 때마다 두 노드의 분리집합을 합쳐야 한다.
 */

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> N;
    int Q; cin >> Q;

    parent.resize(N+1, -1);

    for (int i = 0; i < N-1; i++) {
        int from = i + 2;
        int to; cin >> to;
        parent[from] = to;
    }

    vtiii queries(N-1+Q);
    for (int i = 0; i < (N - 1) + Q; i++) {
        int query; cin >> query;
        if (query == 0) {
            int node; cin >> node;
            queries[i] = {0, node, 0};            
        } else {
            int nodeA, nodeB;
            cin >> nodeA >> nodeB;
            queries[i] = {1, nodeA, nodeB};
        }
    }

    p.resize(N+1, -1);
    vint ret;
    reverse(queries.begin(), queries.end());
    for (auto [query, nodeA, nodeB]: queries) {
        if (query == 0) p[nodeA] = parent[nodeA];
        else {
            if (find(nodeA) == find(nodeB)) ret.push_back(true);
            else ret.push_back(false);
        }
    }

    reverse(ret.begin(), ret.end());
    for (int r: ret) {
        if (r) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}