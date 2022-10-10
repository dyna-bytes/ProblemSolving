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

ll solve(int N, int K, multimap<ll, ll, greater<ll>>& jewelries, multiset<int>& bags) {
    ll ret = 0; 
    for(auto jewelry: jewelries) {
        auto [value, weight] = jewelry;
        
        auto right = bags.lower_bound(weight);
        if (right == bags.end()) continue;

        bags.erase(right);
        ret += value;
    }
    
    return ret;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N, K;
    cin >> N >> K;
    multimap<ll, ll, greater<ll>> jewelries;
    multiset<int> bags;

    for (int i = 0; i < N; i++) {
        ll weight, value; 
        cin >> weight >> value;
        jewelries.insert({value, weight});
    }   

    for (int i = 0; i < K; i++) {
        int weight; cin >> weight;
        bags.insert(weight);
    }

    cout << solve(N, K, jewelries, bags);    
    return 0;
}