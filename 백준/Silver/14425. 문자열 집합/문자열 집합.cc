#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
using namespace std;
typedef vector<int> vint;
#define MAX_CHILD 27
#define debug(x) cout << "[debug] " << #x << " is " << x << '\n'
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)

struct Trie {
    bool accepting;
    bool childExist;
    Trie* child[MAX_CHILD];
    Trie() {
        accepting = childExist = false;
        fill(child, child + MAX_CHILD, nullptr);
    }
    ~Trie() {
        for (int i = 0; i < MAX_CHILD; i++)
            if (child[i]) delete child[i];
    }
    void insert(char* key) {
        if (*key == '\0') {
            accepting = true;
            return;
        }

        int next = *key - 'a';
        if (!child[next]) child[next] = new Trie();
        childExist = true;
        child[next]->insert(key + 1);
    }
    bool exist(char* key) {
        if (*key == '\0') return accepting;
        
        int next = *key - 'a';
        if (!childExist || !child[next]) return false;
        return child[next]->exist(key + 1);
    }
};

int main() {
    FASTIO;
    int N, M;
    cin >> N >> M;

    Trie* root = new Trie();
    for (int i = 0; i < N; i++) {
        char str[501]; cin >> str;
        root->insert(str);
    }

    int cnt = 0;
    for (int i = 0; i < M; i++) {
        char str[501]; cin >> str;
        if (root->exist(str)) cnt++;
    }

    cout << cnt;
    return 0;
}