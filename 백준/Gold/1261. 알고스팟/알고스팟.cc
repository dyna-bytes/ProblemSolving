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
typedef pair<int, P> node;
const int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, -1, 1};

struct BFS_01{
    int Y, X;
    vector<vector<int>> room;
    vector<vector<int>> visited;
    BFS_01(int y, int x){
        Y = y, X = x;
        room.resize(Y+1, vector<int>(X+1));
        visited.resize(Y+1, vector<int>(X+1));
    } 
    bool inRange(int y, int x){
        return (y >= 0 && y < Y && x >= 0 && x < X);
    }
    int run(){
        deque<node> dq;
        dq.push_back({0, {0, 0}});
        visited[0][0] = true;

        while(!dq.empty()){
            node curr = dq.front();
            dq.pop_front();

            int sum = curr.first;
            P pos = curr.second;
            int y = pos.first, x = pos.second;

            if (y == Y-1 && x == X-1) return sum;
            
            for(int d = 0; d < 4; d++){
                int ny = y + dy[d], nx = x + dx[d];

                if (!inRange(ny, nx)) continue;
                if (visited[ny][nx]) continue;
                if (room[ny][nx] == 0){ // room
                    dq.push_front({sum, {ny, nx}}); // higher priority
                    visited[ny][nx] = true;
                }
                else if (room[ny][nx] == 1){ // wall
                    dq.push_back({sum+1, {ny, nx}}); // lower priority
                    visited[ny][nx] = true;
                }
            }
        }
        return -1;
    }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int X, Y; cin >> X >> Y;
    BFS_01 bfs(Y, X);
    for(int y = 0; y < Y; y++){
        string inp; cin >> inp;
        for(int x = 0; x < X; x++)
            bfs.room[y][x] = inp[x] - '0';
    }
    cout << bfs.run();

    return 0;
}