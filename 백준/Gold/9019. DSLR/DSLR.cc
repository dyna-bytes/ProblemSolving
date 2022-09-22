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
const int MOD = 10000;

int leftRotate(int n) {
    int d1 = n / 1000;
    n %= 1000;
    
    int d2 = n / 100;
    n %= 100;

    int d3 = n / 10;
    n %= 10;

    int d4 = n;

    return d2*1000 + d3*100 + d4*10 + d1;
}

int rightRotate(int n) {
    int d1 = n / 1000;
    n %= 1000;
    
    int d2 = n / 100;
    n %= 100;

    int d3 = n / 10;
    n %= 10;

    int d4 = n;

    return d4*1000 + d1*100 + d2*10 + d3;
}

void bfs(int S, int E) {
    vint visited(MOD + 1);
    vpii prev(MOD + 1);
    queue<int> q;

    visited[S] = true;
    q.push(S);

    int ret = MOD;
    while (!q.empty()) {
        int n = q.front(); q.pop();
        if (n == E) break;
        
        // try D operation
        int next_n = 2*n % MOD;
        if (!visited[next_n]) {
            visited[next_n] = true;
            prev[next_n] = {n, 'D'};
            q.push(next_n);
        }

        // try S operation
        next_n = (n - 1 >= 0 ? n - 1 : 9999);
        if (!visited[next_n]) {
            visited[next_n] = true;
            prev[next_n] = {n, 'S'};
            q.push(next_n);
        }

        // try L operation
        next_n = leftRotate(n);
        if (!visited[next_n]) {
            visited[next_n] = true;
            prev[next_n] = {n, 'L'};
            q.push(next_n);
        }
    
        // try R operation
        next_n = rightRotate(n);
        if (!visited[next_n]) {
            visited[next_n] = true;
            prev[next_n] = {n, 'R'};
            q.push(next_n);
        }
    }

    vint tracking;
    for (int n = E; n != S; n = prev[n].first)
        tracking.push_back(prev[n].second);

    reverse(tracking.begin(), tracking.end());
    for (int n: tracking) cout << (char)n; 
    cout << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int T; cin >> T;
    while (T--) {
        int S, E; cin >> S >> E;
        bfs(S, E);
    }
    return 0;
}