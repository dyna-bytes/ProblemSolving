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

const int MAXN = 20;
int N;
int S[MAXN + 1][MAXN + 1];

int ans = INT_MAX;
int teamA[MAXN + 1];
int teamB[MAXN + 1];
int used[MAXN + 1];
void nCr(int curr = -1, int cnt = 0) {
    if (cnt == N/2) {
        int a = 0, b = 0;
        for (int i = 0; i < N; i++) 
            (used[i] ? teamA[a++] : teamB[b++]) = i;
            
        int scoreA = 0, scoreB = 0;
        for (int i = 0; i < N/2; i++)
            for (int j = 0; j < N/2; j++) {
                scoreA += S[teamA[i]][teamA[j]];
                scoreB += S[teamB[i]][teamB[j]];
            }
        
        ans = min(ans, abs(scoreA - scoreB));
        return;
    }

    for (int next = curr + 1; next < N; next++) {
        if (used[next]) continue;
        used[next] = true;
        nCr(next, cnt + 1);

        used[next] = false;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> N;
    for (int y = 0; y < N; y++)
        for (int x = 0; x < N; x++)
            cin >> S[y][x];

    nCr();
    cout << ans << endl;
    return 0;
}