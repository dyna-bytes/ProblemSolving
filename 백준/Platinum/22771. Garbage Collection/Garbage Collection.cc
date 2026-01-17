#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define DBG
#ifdef DBG
#define debug(x) cout << "[" << __func__ << "](" << __LINE__ << ") " << #x << " is " << x << endl;
#else
#define debug(x)
#endif

enum Operations {
    ALLOC = 0,
    CALL,
    LINK,
    RETURN,
};

const int MAXL = 100000;

class UnionFind {
    vector<int> parents;   // parent node index
    vector<int> size;      // set size (heap object count)
    vector<int> ref_count; // active stack reference count

public:
    UnionFind(int n) {
        parents.resize(n + 1);
        size.resize(n + 1, 1);
        ref_count.resize(n + 1, 1);
        for(int i=0; i<=n; i++) parents[i] = i;
    }

    int find(int x) {
        if (parents[x] == x) return x;
        return parents[x] = find(parents[x]); // Path Compression
    }

    void merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return;

        parents[v] = u;
        size[u] += size[v];
        ref_count[u] += ref_count[v];
    }

    int dereference(int x) {
        int root = find(x);
        ref_count[root]--;

        if (ref_count[root] == 0) {
            return size[root];
        }
        return 0;
    }
};

void solve(int n, vector<vector<int>>& ops) {
    UnionFind uf(n);
    int var = 0;

    stack<vector<int>> stack_frames;
    stack_frames.push({ });

    for (auto& op: ops) {
        if (op[0] == ALLOC) {
            ++var;
            stack_frames.top().push_back(var);

        } else if (op[0] == CALL) {
            stack_frames.push({ });

        } else if (op[0] == LINK) {
            uf.merge(op[1], op[2]);

        } else if (op[0] == RETURN) {
            int unlinked = 0;
            for (int v: stack_frames.top()) {
                unlinked += uf.dereference(v);
            }
            cout << unlinked << endl;
            stack_frames.pop();
        }
    }
}

int main() {
    FASTIO;
    int cnt = 0;
    while (true) {
        int n;
        cin >> n;
        if (n == 0) break;

        vector<vector<int>> ops(n);
        for (int i = 0; i < n; i++) {
            string inp; cin >> inp;
            if (inp.find("alloc") != string::npos)
                ops[i] = { ALLOC };
            else if (inp.find("call") != string::npos)
                ops[i] = { CALL };
            else if (inp.find("link") != string::npos) {
                ops[i] = { LINK };
                for (int j = 0; j < 2; j++) {
                    int mem; cin >> mem;
                    ops[i].push_back(mem);
                }
            } else if (inp.find("return") != string::npos)
                ops[i] = { RETURN };
        }

        cout << "Program #" << (++cnt) << endl;
        solve(n, ops);
    }

    return 0;
}