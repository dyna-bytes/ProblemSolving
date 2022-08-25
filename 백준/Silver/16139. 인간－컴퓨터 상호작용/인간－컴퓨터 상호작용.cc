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

    string S; cin >> S;
    vector<vint> pSum(26, vint(S.size() + 1));
    for (int i = 0; i < S.size(); i++) {
        int ch = S[i] - 'a';
        pSum[ch][i+1]++;

        for (int j = 0; j < 26; j++)
            pSum[j][i+1] += pSum[j][i];
    }

    // debugV2D(pSum);

    int Q; cin >> Q;
    for (int i = 0; i < Q; i++) {
        char ch;
        int l, r; 
        cin >> ch >> l >> r;
        
        ch -= 'a';
        cout << (pSum[ch][r+1] - pSum[ch][l]) << endl;
    }
    
    return 0;
}