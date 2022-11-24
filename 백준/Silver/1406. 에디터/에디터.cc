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
typedef list<char>::iterator iter;

list<char> lst;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    char str[100001]; cin >> str;
    for (int i = 0; str[i]; i++)
        lst.push_back(str[i]);
    
    iter it = lst.end();
    int M; cin >> M;
    for (int i = 0; i < M; i++) {
        string op; cin >> op;
        if (op == "L") {
            if (it != lst.begin()) it--;
        }
        if (op == "D") {
            if (it != lst.end()) it++;
        }
        if (op == "B") {
            if (it != lst.begin()) lst.erase(prev(it));
        }
        if (op == "P") {
            char x; cin >> x;
            lst.insert(it, x);
        }
    }
    for (char x: lst) cout << x;
    return 0;
}