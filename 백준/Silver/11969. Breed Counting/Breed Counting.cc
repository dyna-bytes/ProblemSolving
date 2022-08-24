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

    int N, Q;
    cin >> N >> Q;
    vint pSum1(N+1), pSum2(N+1), pSum3(N+1);

    for (int i = 0; i < N; i++) {
        int val; cin >> val;
        if (val == 1) pSum1[i+1]++;
        else if (val == 2) pSum2[i+1]++;
        else if (val == 3) pSum3[i+1]++;

        pSum1[i+1] += pSum1[i];
        pSum2[i+1] += pSum2[i];
        pSum3[i+1] += pSum3[i];
    }

    for (int i = 0; i < Q; i++) {
        int a, b; cin >> a >> b;
        cout << (pSum1[b] - pSum1[a-1]) << " ";
        cout << (pSum2[b] - pSum2[a-1]) << " ";
        cout << (pSum3[b] - pSum3[a-1]) << endl;
    }
    
    return 0;
}