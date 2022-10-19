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

const int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1}, dx[] = {0, 1, 1, 1, 0, -1, -1, -1};

int Y, X;
vector<vector<char>> A;

string S;
int S_size;
map<tiii, int> dp;

int dfs(int y, int x, int curr) {
    if (curr == S_size - 1) return 1;

    int& ret = dp[{y, x, curr}];
    if (ret) return ret;

    ret = 0;
    for (int d = 0; d < 8; d++) {
        int ny = (y + dy[d] + Y) % Y;
        int nx = (x + dx[d] + X) % X;

        if (S[curr + 1] == A[ny][nx])
            ret += dfs(ny, nx, curr + 1);
    }

    return ret;
}

void solve(int K, vector<string> query) {
    for (string query_str: query) {
        S = query_str;
        S_size = query_str.size();

        dp.clear();
        int res = 0;
        
        for (int y = 0; y < Y; y++)
            for (int x = 0; x < X; x++)
                if (S[0] == A[y][x]) res += dfs(y, x, 0);

        cout << res << endl;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int K;
    cin >> Y >> X >> K;

    A.resize(Y, vector<char>(X));
    vector<string> query(K);

    for (int y = 0; y < Y; y++) {
        string inp; cin >> inp;
        for (int x = 0; x < X; x++)
            A[y][x] = inp[x];
    }

    for (int k = 0; k < K; k++)
        cin >> query[k];

    solve(K, query);
    return 0;
}