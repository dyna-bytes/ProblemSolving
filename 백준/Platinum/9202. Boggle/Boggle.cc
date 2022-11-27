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
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vint;
typedef vector<char> vchar;
typedef vector<pii> vpii;
const int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1}, dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
const int score[] = {0, 0, 0, 1, 1, 2, 3, 5, 11};
const int B_SIZE = 4;

bool inRange(int y, int x) {return y >= 0 && y < B_SIZE && x >= 0 && x < B_SIZE; }
struct Trie {
    bool output = false;
    bool child_exist = false;
    map<char, Trie*> childs;
    ~Trie() {
        for (auto child: childs) {
            delete child.second;
        }
    }
    void insert(char* key) {
        if (*key == '\0') {
            output = true;
            return;
        }

        if (!childs[*key]) childs[*key] = new Trie();
        child_exist = true;
        childs[*key]->insert(key + 1);
    }
};

class Solution {
public:
    set<string> found_words;
    vector<vchar> board;
    vector<vint> visited;
    Solution() {
        found_words = {};
        board = vector<vchar>(B_SIZE, vchar(B_SIZE, 0));
        visited = vector<vint>(B_SIZE, vint(B_SIZE, 0));
    }

    void dfs(int y, int x, Trie* curr, string& str) {
        if (curr->output) {
            found_words.insert(str);
            if (!curr->child_exist) return;
        }

        for (int d = 0; d < 8; d++) {
            int ny = y + dy[d], nx = x + dx[d];
            if (!inRange(ny, nx)) continue;
            if (visited[ny][nx]) continue;
            if (curr->childs[board[ny][nx]] == nullptr) continue;
            str += board[ny][nx];
            visited[ny][nx] = true;
            dfs(ny, nx, curr->childs[board[ny][nx]], str);
            visited[ny][nx] = false;
            str = str.substr(0, str.size() - 1);
        }
    }

    void solve(Trie* root) {
        for (int y = 0; y < B_SIZE; y++)
            for (int x = 0; x < B_SIZE; x++) {
                if (root->childs[board[y][x]]) {
                    string str; str += board[y][x];
                    visited[y][x] = true;
                    dfs(y, x, root->childs[board[y][x]], str);
                    visited[y][x] = false;
                }
            }
        
        int summed_score = 0;
        string longest = "";
        int cnt = found_words.size();
        for (auto str: found_words) {
            if (longest.size() < str.size()) 
                longest = str;
            summed_score += score[str.size()];
        }

        cout << summed_score << " " << longest << " " << cnt << endl;
    }
};

int main(){
    Trie* root = new Trie();
    int W; cin >> W;
    for (int i = 0; i < W; i++) {
        char word[9]; cin >> word;
        root->insert(word);
    }

    int B; cin >> B;
    while (B--) {
        Solution sol = Solution();
        for (int y = 0; y < B_SIZE; y++)
            for (int x = 0; x < B_SIZE; x++)
                cin >> sol.board[y][x];
        
        sol.solve(root);
    }
    return 0;
}