#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#define endl '\n'
#define debug(x) cout << "[debug] " << #x << " is " << x << endl
#define debugVec(v) do{\
    cout << "[debug] " << #v << endl;\
    for (auto e : v) cout << e << " | ";\
    cout << endl;\
}while(0)
using namespace std;
typedef long long ll;
const int CHILD_MAX = 26;

struct Trie {
    bool output;
    int branch; // 자식 노드의 개수
    int words; // 현재 노드의 서브트리에 있는 단어의 개수
    Trie* childs[CHILD_MAX];
    Trie() {
        output = false;
        branch = words = 0;
        fill(childs, childs + CHILD_MAX, nullptr);
    }
    ~Trie() {
        for (int i = 0; i < CHILD_MAX; i++)
            if (childs[i]) delete childs[i];
    }
    void insert(const char* key) {
        if (*key == '\0') {
            output = true;
            branch++;
            return;
        }

        int next = *key - 'a';
        if (!childs[next]) {
            childs[next] = new Trie();
            branch++;
        }

        words++;
        childs[next]->insert(key + 1);
    }
    ll countWords(bool isRoot = false) {
        ll res = 0;

        for (int i = 0; i < CHILD_MAX; i++)
            if (childs[i]) res += childs[i]->countWords();
        
        if (isRoot || branch > 1) res += words; // 분기점에 도달하면, 단어의 개수 = 단어를 구분하기 위한 최소 타이핑 수

        return res;
    }
};

char words[100000 + 1][81];

int main() {
    int N;
    while (scanf("%d", &N) > 0) {
        memset(words, 0, sizeof(words));
        Trie* root = new Trie();

        for (int i = 0; i < N; i++) {
            scanf("%s", words[i]);
            root->insert(words[i]);
        }
        double res = 1.0 * root->countWords(true) / N;
        printf("%.2lf\n", res);
        delete root;
    }
    return 0;
}