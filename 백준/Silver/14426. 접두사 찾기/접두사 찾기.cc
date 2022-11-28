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

const int ROOT = 1;
int unused = 2;
const int MAX = 10000 * 500 + 1;
bool output[MAX];
int nxt[MAX][26];

void insert(string& s) {
    int cur = ROOT;
    for (char ch: s) {
        if (nxt[cur][ch - 'a'] == -1)
            nxt[cur][ch - 'a'] = unused++;
        cur = nxt[cur][ch - 'a'];
        output[cur] = true;
    }
}

bool find(string& s) {
    int cur = ROOT;
    for (char ch: s) {
        if (nxt[cur][ch - 'a'] == -1) return false;
        cur = nxt[cur][ch - 'a'];
    }
    
    return output[cur];
} 

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    for (int i = 0; i < MAX; i++)
        fill(nxt[i], nxt[i] + 26, -1);

    int N, M; cin >> N >> M;
    for (int i = 0; i < N; i++) {
        string str; cin >> str;
        insert(str);
    }

    int cnt = 0;
    for (int i = 0; i < M; i++) {
        string key; cin >> key;
        cnt += find(key);
    }
    cout << cnt;

    return 0;
}