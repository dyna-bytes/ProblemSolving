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

string solve(string& str, string& bomb) {
    stack<char> S;
    for (char ch: str) {
        S.push(ch);
        
        if (S.size() >= bomb.size() && S.top() == bomb.back()) {
            stack<char> restore;
            for (int i = bomb.size() - 1; i >= 0; i--) {
                if (S.top() == bomb[i]) {
                    restore.push(S.top());
                    S.pop();
                } else {
                    while (!restore.empty()) {
                        S.push(restore.top());
                        restore.pop();
                    }
                    break;
                }
            }
        }
    }
    
    if (S.empty()) return "FRULA";
    string ret;
    while (!S.empty()) {
        ret += S.top();
        S.pop();
    }
    reverse(ret.begin(), ret.end());
    return ret;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    string str;
    cin >> str;
    string bomb;
    cin >> bomb;

    cout << solve(str, bomb);
    return 0;
}