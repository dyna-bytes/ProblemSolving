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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    set<pii> s;
    map<int, int> hash;

    int N; cin >> N;
    for (int i = 0; i < N; i++) {
        int P, L; cin >> P >> L;
        s.insert({L, P});
        hash.insert({P, L});
    }

    int Q; cin >> Q;
    for (int i = 0; i < Q; i++) {
        string query; cin >> query;
        if (query == "recommend") {
            int x; cin >> x;
            if (x == 1) cout << prev(s.end())->second << endl;
            if (x == -1) cout << s.begin()->second << endl;
        } else if (query == "add") {
            int P, L; cin >> P >> L;
            s.insert({L, P});
            hash.insert({P, L});
        } else if (query == "solved") {
            int P; cin >> P;
            auto hash_it = hash.find(P);
            int L = hash_it->second;
            
            hash.erase(hash_it);
            s.erase({L, P});
        }
    }
    
    return 0;
}