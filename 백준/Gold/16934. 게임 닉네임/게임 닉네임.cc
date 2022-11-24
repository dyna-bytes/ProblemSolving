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
const int C_MAX = 26;
const int INF = 1e9;

struct Trie {
    int output;
    Trie* childs[C_MAX];
    Trie() {
        output = 0;
        fill(childs, childs + C_MAX, nullptr);
    }
    int insert(const char* key, const int depth, int& ret_output) {
        if (*key == '\0') {
            ret_output = ++output;
            return depth;
        }
        int ret = INF;
        int next = *key - 'a';
        if (childs[next] == nullptr) { 
            childs[next] = new Trie(); 
            ret = depth + 1;
        }
        return min(ret, childs[next]->insert(key + 1, depth + 1, ret_output));
    }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    Trie* root = new Trie();
    int N; cin >> N;
    for (int i = 0; i < N; i++) {
        char str[11]; cin >> str;
        int output = 0;
        int ret = root->insert(str, 0, output);
        
        for (int j = 0; j < ret; j++) cout << str[j];
        if (output > 1) cout << output;
        cout << endl;
    }
    return 0;
}