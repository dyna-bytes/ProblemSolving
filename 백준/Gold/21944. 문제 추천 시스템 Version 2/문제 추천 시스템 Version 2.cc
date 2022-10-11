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
typedef tuple<int, int, int> tiii;
typedef vector<int> vint;
typedef vector<pii> vpii;

set<tiii> G; // {분류, 난이도, 문제번호}
set<pii> S; // {난이도, 문제번호}
map<int, pii> M; // {문제번호, {난이도, 분류}}

int recommend1(int g, int x) {
    if (x == 1) {
        auto it = G.lower_bound({g+1, 0, 0});
        return get<2>(*prev(it));
    } else {
        auto it = G.lower_bound({g, 0, 0});
        return get<2>(*it);
    }
} 

int recommend2(int x) {
    if (x == 1) return prev(S.end())->second;
    else        return S.begin()->second;
}

int recommend3(int x, int l) {
    if (x == 1) {
        auto it = S.lower_bound({l, 0});
        if (it == S.end()) return -1;
        return it->second;
    } else {
        auto it = S.lower_bound({l, 0});
        if (it == S.begin()) return -1;
        return prev(it)->second;
    }
}

void add(int p, int l, int g) {
    G.insert({g, l, p});
    S.insert({l, p});
    M.insert({p, {l, g}});
}

void solved(int p) {
    auto [l, g] = M[p];

    M.erase(p);
    S.erase({l, p});
    auto it = G.find({g, l, p});
    G.erase(it);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N; cin >> N;
    for (int i = 0; i < N; i++) {
        int p, l, g;
        cin >> p >> l >> g;
        add(p, l, g);
    }

    int M; cin >> M;
    for (int i = 0; i < M; i++) {
        string query; cin >> query;

        if (query == "add") {
            int p, l, g; 
            cin >> p >> l >> g;
            add(p, l, g);
        } else if (query == "recommend") {
            int g, x; 
            cin >> g >> x;
            cout << recommend1(g, x) << endl;
        } else if (query == "recommend2") {
            int x;
            cin >> x;
            cout << recommend2(x) << endl;
        } else if (query == "recommend3") {
            int x, l;
            cin >> x >> l;
            cout << recommend3(x, l) << endl;
        } else if (query == "solved") {
            int p; 
            cin >> p;
            solved(p);
        }
    }
    return 0;
}