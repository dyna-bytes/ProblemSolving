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

void add(int& S, int x) {
    S |= (1 << x);
}

void remove(int& S, int x) {
    S &= ~(1 << x);
}

bool check(int& S, int x) {
    return S & (1 << x);
}

void toggle(int& S, int x) {
    S ^= (1 << x);
}

void all(int& S) {
    S = (1 << 21) - 1;
}

void empty(int& S) {
    S = 0;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int S = 0;
    int M; cin >> M;
    for (int i = 0; i < M; i++) {
        string op; cin >> op;
        if (op == "all" || op == "empty") {
            if (op == "all") all(S);
            if (op == "empty") empty(S);
        } else {
            int x; cin >> x;
            if (op == "add") add(S, x);
            if (op == "remove") remove(S, x);
            if (op == "check") cout << check(S, x) << endl;
            if (op == "toggle") toggle(S, x);
        }
    }

    return 0;
}