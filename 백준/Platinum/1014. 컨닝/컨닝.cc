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
        std::cout << "  ["; \
        for(int x = 0; x < ((v[y].size())-1); x++) \
            std::cout << v[y][x] << "|"; \
        std::cout << v[y][(v[y].size())-1] << "]\n"; \
    } \
    std::cout << "]\n"; \
} while(0)
#define endl '\n'
typedef long long ll;
typedef pair<int, int> P;

int Y, X;
vector<vector<int>> dp(10, vector<int>(1 << 10));
vector<vector<char>> board(10, vector<char>(10));
vector<int> cand(10);

// 한 줄에 앉을 수 있는 학생의 배치를 구함
// fill candidatable seats. Caring only adjacenect bits to not become 1.
void dfs(int x, vector<string>& lines){
    if (x == X){
        string line;
        for (int a: cand)
            line += to_string(a);
        lines.push_back(line);
        return;
    }

    cand[x] = 0;
    dfs(x+1, lines);

    if (x == 0 || (x > 0 && cand[x-1] == 0)){
        cand[x] = 1;
        dfs(x+1, lines);
    }
}

int f(int y, int fbits, vector<string>& lines){
    if (y == Y) return 0;
    int& ret = dp[y][fbits];
    if (ret != -1) return ret;
    
    ret = 0; 
    // generate bits state for every possible candidates
    for (string line: lines) { // 앉아 볼 수 있는 모든 후보에 대해 bits 상태를 생성함
        int bits = 0, seats = 0;

        for (int x = 0; x < X; x++) {
            if (line[x] == '0') continue;
            if (board[y][x] == 'x') continue;
            if (x > 0 && fbits & (1 << (x-1))) continue;
            if (x < X && fbits & (1 << (x+1))) continue;

            bits |= (1 << x);
            seats++;
        }
        
        ret = max(ret, f(y+1, bits, lines) + seats);
    }
    return ret;
}

void solve(){
    fill(dp.begin(), dp.end(), vector<int>(dp[0].size(), -1));
    fill(cand.begin(), cand.end(), 0);
    
    cin >> Y >> X;
    for(int y = 0; y < Y; y++)
        for(int x = 0; x < X; x++)
            cin >> board[y][x];

    vector<string> lines;
    dfs(0, lines);
    cout << f(0, 0, lines) << endl;
};

int main(int argc, char** argv){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int T, test_case;

    cin >> T;
    for(test_case = 0; test_case  < T; test_case++){
        solve();
    }

    return 0;
}