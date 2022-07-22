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
typedef vector<int> vint;

struct MaxMatching{
    int N, M;
    vint A, B;
    vector<vint> adj;
    vint visited;
    MaxMatching(int n, int m) {
        N = n, M = m;
        A.resize(N+1, -1), B.resize(M+1, -1);
        adj.resize(N+1);
        visited.resize(N+1);
    }
    void addAdj(int from, int to) { adj[from].push_back(to); }
    bool canMatch(int a) {
        if (visited[a]) return false;
        visited[a] = true;
        for (int b: adj[a]) {
            if (B[b] == -1 || canMatch(B[b])) {
                A[a] = b;
                B[b] = a;
                return true;
            }
        }
        return false;
    }
    int run() {
        int match = 0;
        for (int a = 0; a < N; a++) {
            if (A[a] == -1) {
                fill(visited.begin(), visited.end(), 0);
                if (canMatch(a)) match++;
            }
        }
        return match;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int N, M;
    cin >> N >> M;
    vector<vint> board(N, vint(N, true));
    for (int i = 0; i < M; i++) {
        int y, x; 
        cin >> y >> x;
        y--, x--;
        board[y][x] = false; // 비숍을 놓을 수 없는 칸
    }
    
    vector<vint> Lmap(N, vint(N)), Rmap(N, vint(N)); // 왼쪽 아래 대각선 방향, 오른쪽 아래 대각선 방향
    int num = 0;
    for (int sx = 0; sx < N; sx++) {
        int y_plus_x = sx + 0;
        bool isFirstBishop = false;
        num++;

        for (int x = sx; x >= 0; x--) {
            int y = y_plus_x - x;
            if (board[y][x]) {
                Lmap[y][x] = num;
                isFirstBishop = true;
            } else if (!board[y][x] && isFirstBishop) {
                num++;
                isFirstBishop = false;
            }
        }
    }

    for (int sy = 1; sy < N; sy++) {
        int y_plus_x = sy + N - 1;
        bool isFirstBishop = false;
        num++;
        for (int y = sy; y < N; y++) {
            int x = y_plus_x - y;
            if (board[y][x]) {
                Lmap[y][x] = num;
                isFirstBishop = true;
            } else if (!board[y][x] && isFirstBishop) {
                num++;
                isFirstBishop = false;
            }
        }
    }

    for (int sx = N-1; sx >= 0; sx--) {
        int x_minus_y = sx - 0;
        bool isFirstBishop = false;
        num++;

        for (int x = sx; x < N; x++) {
            int y = x - x_minus_y;
            if (board[y][x]) {
                Rmap[y][x] = num;
                isFirstBishop = true;
            } else if (!board[y][x] && isFirstBishop) {
                num++;
                isFirstBishop = false;
            }
        }
    }

    for (int sy = 1; sy < N; sy++) {
        int y_minus_x = sy - 0;
        bool isFirstBishop = false;
        num++;

        for (int y = sy; y < N; y++) {
            int x = y - y_minus_x;
            if (board[y][x]) {
                Rmap[y][x] = num;
                isFirstBishop = true;
            } else if (!board[y][x] && isFirstBishop) {
                num++;
                isFirstBishop = false;
            }
        }
    }

    // debugV2D(Lmap);
    // debugV2D(Rmap);
    MaxMatching Graph(num, num);
    for (int y = 0; y < N; y++) 
        for (int x = 0; x < N; x++)
            if (board[y][x]) Graph.addAdj(Lmap[y][x], Rmap[y][x]);
    
    cout << Graph.run();
    return 0;
}