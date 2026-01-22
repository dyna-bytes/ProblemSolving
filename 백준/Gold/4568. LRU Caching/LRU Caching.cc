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

enum operations {
    OP_ACCESS,
    OP_PRINT
};

class LRUCache {
    int cap;
    list<char> lru;
    unordered_map<char, list<char>::iterator> cache;
public:
    LRUCache(int n) {
        cap = n;
    }
    void read(char data) {
        auto it = cache[data];
        lru.erase(it);
        lru.push_back(data);
        cache[data] = prev(lru.end());
    }
    void write(char data) {
        if (lru.size() >= cap) {
            char victim = lru.front();
            cache.erase(victim);
            lru.pop_front();
        }

        lru.push_back(data);
        cache[data] = prev(lru.end());
    }
    void access(char data) {
        if (cache.count(data)) read(data);
        else write(data);
    }
    void print() {
        for (auto it: lru)
            cout << it;
        cout << endl;
    }
};

void solve(int n, vector<vector<int>>& ops) {
    LRUCache LRU(n);
    for (vector<int>& op: ops) {
        if (op[0] == OP_ACCESS) LRU.access(op[1]);
        else if (op[0] == OP_PRINT) LRU.print();
    }
}

int main() {
    FASTIO;
    int cnt = 0;
    while (true) {
        int n; cin >> n;
        if (n == 0) break;

        string inp; cin >> inp;
        vector<vector<int>> ops(inp.size());

        for (int i = 0; i < inp.size(); i++) {
            char ch = inp[i];
            if (ch == '!') ops[i] = { OP_PRINT };
            else ops[i] = { OP_ACCESS, ch };
        }

        cout << "Simulation " << ++cnt << endl;
        solve(n, ops);
    }
    return 0;
}