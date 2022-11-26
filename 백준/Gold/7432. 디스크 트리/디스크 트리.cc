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
typedef vector<int> vint;
typedef vector<pii> vpii;
typedef list<string>::iterator iter;

struct Trie {
    map<string, Trie*> childs;
    void insert(iter it, iter end) {
        if (it == end) return;

        if (childs[*it] == nullptr) childs[*it] = new Trie();
        childs[*it]->insert(++it, end);
    }
    void dfs(Trie* curr = nullptr, int depth = 0) {
        if (curr == nullptr) curr = this;
        for (auto& [str, child]: curr->childs) {
            for (int i = 0; i < depth; i++) cout << ' ';
            cout << str << endl;
            dfs(child, depth + 1);
        }
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N; cin >> N;
    Trie* root = new Trie();
    for (int i = 0; i < N; i++) {
        string inp; cin >> inp;
        list<string> path;
        istringstream iss(inp);
        string strbuf;
        while (getline(iss, strbuf, '\\')) {
            path.push_back(strbuf);
        }
        root->insert(path.begin(), path.end());
    }
    root->dfs();
    return 0;
}