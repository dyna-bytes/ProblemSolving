#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
using namespace std;
typedef pair<int, int> pii;
typedef vector<int> vint;
typedef list<string>::iterator iter;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define debug(x) cout << "[debug] " << #x << " is " << x << endl

list<string> L;

struct Trie {
    bool final_state;
    bool child_exist;
    map<string, Trie*> child;
    Trie() {
        final_state = child_exist = false;
        child = {};
    }
    ~Trie() {
        child = {};
    }
    void insert(iter it) {
        if (it == L.end()) {
            final_state = true;
            return;
        }

        if (child[*it] == nullptr)
            child[*it] = new Trie();

        child_exist = true;
        child[*it]->insert(++it);
    }
};

void dfs(Trie* curr, int depth) {
    if (curr->final_state) return;

    for (auto [n_str, next] : curr->child) {
        for (int i = 0; i < depth; i++) cout << "--";
        cout << n_str << endl;
        dfs(next, depth + 1);
    }
}

int main() {
    FASTIO;
    int N; cin >> N;
    Trie* root = new Trie();
    for (int i = 0; i < N; i++) {
        int K; cin >> K;
        L = {};
        for (int j = 0; j < K; j++) {
            string str; cin >> str;
            L.push_back(str);
        }
        root->insert(L.begin());
    }

    dfs(root, 0);

    return 0;
}