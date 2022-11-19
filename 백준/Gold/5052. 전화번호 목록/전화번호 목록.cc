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

const int CHILD_MAX = 10;

struct Trie {
    Trie* childs[CHILD_MAX];
    bool final_state;
    bool child_exist;

    Trie() {
        fill(childs, childs + CHILD_MAX, nullptr);
        final_state = child_exist = false;
    }
    ~Trie() {
        for (int i = 0; i < CHILD_MAX; i++)
            if (childs[i]) delete childs[i];
    }
    // 문자열 key를 현재 노드부터 삽입
    void insert(const char* key) {
        if (*key == '\0') final_state = true;
        else {
            int next = *key - '0';
            if (!childs[next]) childs[next] = new Trie();
            child_exist = true;

            childs[next]->insert(key + 1);
        }
    }

    bool isConsistent() {
        if (child_exist && final_state) return false;

        for (int i = 0; i < CHILD_MAX; i++)
            if (childs[i] && !childs[i]->isConsistent()) return false;
        return true;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        Trie* root = new Trie();
        for (int i = 0; i < N; i++) {   
            char tel[11]; cin >> tel;
            
            root->insert(tel);
        }
        cout << (root->isConsistent() ? "YES" : "NO") << endl;
        delete root;
    }
    return 0;
}