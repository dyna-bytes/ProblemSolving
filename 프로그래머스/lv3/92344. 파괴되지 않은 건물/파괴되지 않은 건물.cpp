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
#define ATTACK 1
#define HEAL 2

int solution(vector<vector<int>> board, vector<vector<int>> skill) {
    int answer = 0;
    int Y = board.size();
    int X = board[0].size();

    vector<vector<int>> prefix_sum(Y+1, vector<int>(X+1));
    for(auto vint: skill){
        int type = vint[0], y1 = vint[1], x1 = vint[2],
            y2 = vint[3], x2 = vint[4], degree = vint[5];

        if (type == HEAL) {
            prefix_sum[y1][x1] += degree;
            prefix_sum[y1][x2+1] -= degree;
            prefix_sum[y2+1][x1] -= degree;
            prefix_sum[y2+1][x2+1] += degree;
        } else {
            prefix_sum[y1][x1] -= degree;
            prefix_sum[y1][x2+1] += degree;
            prefix_sum[y2+1][x1] += degree;
            prefix_sum[y2+1][x2+1] -= degree;
        }
    }

    for(int y = 0; y < Y; y++)
        for(int x = 0; x < X; x++)
            prefix_sum[y][x+1] += prefix_sum[y][x];

    for(int y = 0; y < Y; y++)
        for(int x = 0; x < X; x++)
            prefix_sum[y+1][x] += prefix_sum[y][x];        
    
    for(int y = 0; y < Y; y++){
        for(int x = 0; x < X; x++){
            board[y][x] += prefix_sum[y][x];
            if (board[y][x] > 0) answer++;
        }
    }

    // debugV2D(board);
    return answer;
}