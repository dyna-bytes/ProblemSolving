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
typedef vector<int> vint;
typedef vector<pii> vpii;

struct UnionFind{
    vector<int> parent;
    UnionFind(int n) {
        parent.resize(n, -1);
    }
    // find root
    int find(int curr) {
        if (parent[curr] < 0) return curr;
        return parent[curr] = find(parent[curr]);
    }
    // union two roots. return true if they can be unioned.
    bool merge(int from, int to) {
        from = find(from); // from 노드의 루트를 찾음
        to = find(to);     // to 노드의 루트를 찾음
        if (from == to) return false;

        if (abs(parent[from]) > abs(parent[to])) swap(from, to);
        parent[to] += parent[from]; // from 루트의 자식의 수를 to 루트의 자식의 수에 더함
        parent[from] = to; // from 루트의 부모를 to 루트로 삼음
        return true;
    }
    // count tree size
    int count(int root) {
        root = find(root);
        return abs(parent[root]);
    }
};

const int UNION = 0;
const int FIND = 1;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    // Usage example
    // problem BOJ 1717: https://www.acmicpc.net/problem/1717

    int N, M;
    cin >> N >> M;
    UnionFind Tree(N+1);

    for (int i = 0; i < M; i++) {
        int query, a, b; 
        cin >> query >> a >> b;
        if (query == UNION) Tree.merge(a, b);
        if (query == FIND) {
            if (Tree.find(a) == Tree.find(b)) cout << "YES" << endl;
            else cout << "NO" << endl;
        }
    } 
    
    return 0;
}