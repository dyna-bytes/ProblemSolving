#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <string>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define debug(x) cout << "[debug] " << #x << " is " << x << endl
struct Trie {
    int output = 0;
    int remove = 0;
    map<char, Trie*> childs;
    ~Trie() {
        childs = {};
    }
    void insert(char* key, bool _remove = true) {
        this->remove = (_remove) ? 1 : -1;
        
        if (*key == '\0') {
            this->output = (_remove) ? 1 : -1;
            return;
        }

        if (childs[*key] == nullptr) childs[*key] = new Trie();
        childs[*key]->insert(key + 1, _remove);
    }
};

int dfs(Trie* curr) {    
    if (curr->remove != -1) return 1;
    
    int ret = (curr->output == 1);
    for (auto [ch, child] : curr->childs)
        ret += dfs(child);
    
    return ret;
}



int main() {
    FASTIO;
    int T; cin >> T;
    while (T--) {
        Trie* root = new Trie();
        int N1; cin >> N1;
        for (int i = 0; i < N1; i++) {
            char file[21]; cin >> file;
            root->insert(file, true);
        }
        int N2; cin >> N2;
        for (int i = 0; i < N2; i++) {
            char file[21]; cin >> file;
            root->insert(file, false);
        }

        cout << dfs(root) << endl;
        delete root;
    }
    return 0;
}