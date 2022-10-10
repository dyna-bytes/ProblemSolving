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

int N;
set<int> S;

int curr = 0;
void setting(int i) {
    auto iter = S.find(i);
    if (iter != S.end()) S.erase(iter);
    else S.insert(i);
}

void move(int x) {
    curr += x;
    if (curr >= N) curr %= N;
}

int find() {
    if (S.empty()) return -1;

    auto right = S.lower_bound(curr);
    if (right != S.end()) 
        return *right - curr;
    
    return *S.begin() + N - curr;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int Q; cin >> N >> Q;

    for (int i = 0; i < N; i++){ 
        int A; cin >> A;
        if (A) S.insert(i);
    }

    for (int i = 0; i < Q; i++) {
        int query; cin >> query;
        int x;
        if (query == 1) {
            cin >> x;
            x--;
            setting(x);
        } else if (query == 2) {
            cin >> x;
            move(x);
        } else {
            cout << find() << endl;
        }
    }
    return 0;
}