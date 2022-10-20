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
    
    int N, Q; cin >> N >> Q;

    map<string, set<string>> team_to_members;
    map<string, string> member_to_team;

    for (int i = 0; i < N; i++) {
        string team; cin >> team;
        int n; cin >> n;
        for (int j = 0; j < n; j++) {
            string member; cin >> member;
            team_to_members[team].insert(member);
            member_to_team[member] = team;
        }
    }

    for (int i = 0; i < Q; i++) {
        string query; cin >> query;
        int quiz; cin >> quiz;

        if (quiz ==  0) {
            auto it = team_to_members.find(query);
            for (auto set_it = it->second.begin(); set_it != it->second.end(); set_it++)
                cout << *set_it << endl;
        } else {
            cout << member_to_team[query] << endl;
        }
    }
    return 0;
}