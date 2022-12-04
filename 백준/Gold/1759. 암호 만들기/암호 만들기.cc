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

int L, C;
vector<char> A;
string ans;
map<char, int> isVowel;

void dfs(int pos, int cnt, int consonant, int vowel) {
    if (cnt == L) {
        if (consonant >= 2 && vowel >= 1) cout << ans << endl;
        return;
    }

    for (int next = pos + 1; next < C; next++) {
        ans.push_back(A[next]);
        dfs(next, cnt + 1, consonant + !isVowel[A[next]], vowel + isVowel[A[next]]);
        ans.pop_back();
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> L >> C;
    A.resize(C);
    for (char& ch: A) cin >> ch;
    sort(A.begin(), A.end());

    isVowel['a'] = isVowel['e'] = isVowel['i'] = isVowel['o'] = isVowel['u'] = true;
    dfs(-1, 0, 0, 0);
    return 0;
}