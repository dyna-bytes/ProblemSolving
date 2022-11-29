#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define debug(x) cout << "[debug] " << #x << " is " << x << endl
#define debugVec(v) do{\
    cout << "[debug] " << #v << endl;\
    for (auto e: v) cout << e << " | ";\
    cout << endl;\
}while(0)
typedef pair<int, int> pii;
typedef vector<int> vint;
typedef vector<pii> vpii;

string ans; // global
struct Trie {
    bool output;
    bool visited;
    Trie* childs[2];
    Trie() {
        output = false;
        visited = false;
        childs[0] = childs[1] = nullptr;
    }
    bool insert(int len) {
        if (len == 0) {
            if (visited) return false;
            return visited = true;
        }

        for (int i = 0; i < 2; i++) {
            if (!childs[i]) childs[i] = new Trie();
            ans.push_back(i + '0');
            if (childs[i]->insert(len - 1)) 
                return visited = true;
            
            ans.pop_back();
        }
        return false;
    }
};


int main() {
    int N; cin >> N;
    vpii L(N);
    vector<string> answers(N);
    for (int i = 0; i < N; i++) 
        cin >> L[i].first, L[i].second = i;

    // 가장 긴 단어부터 만들어가나감
    sort(L.rbegin(), L.rend());
    Trie* root = new Trie();
    for (int i = 0; i < N; i++) {
        ans = "";
        bool possible = root->insert(L[i].first);
        if (!possible) {
            cout << -1;
            return 0;
        }
        answers[L[i].second] = ans;
    }


    cout << 1 << endl;
    for (auto str: answers) cout << str << endl;

    return 0;
}