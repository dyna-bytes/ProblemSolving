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

int N = 3;
int NN = 9;

int x_map[9][10];
int y_map[9][10];
int z_map[9][10];
int board[9][9];

bool isValidSudoku() {
    int num;
    int z;
    for (int y = 0; y < NN; ++y)
        for (int x = 0; x < NN; ++x) {
            num = board[y][x];
            z = (y / N) * N + x / N;
            if (num > NN) return false;
            if (x_map[x][num]) return false;
            if (y_map[y][num]) return false;
            if (z_map[z][num]) return false;

            x_map[x][num] = true;
            y_map[y][num] = true;
            z_map[z][num] = true;
        }
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        cout << "Case #" << t << ": ";

        cin >> N;
        NN = N * N;
        memset(x_map, 0, sizeof(x_map));
        memset(y_map, 0, sizeof(y_map));
        memset(z_map, 0, sizeof(z_map));
        for (int y = 0; y < NN; ++y)
            for (int x = 0; x < NN; ++x)
                cin >> board[y][x];
        bool res = isValidSudoku();
        if (res) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    return 0;
}