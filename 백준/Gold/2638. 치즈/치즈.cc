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
const int dy[] = {-1, 1, 0, 0}, dx[] = {0, 0, -1, 1};
#define AIR 2
#define CHEESE 1
#define HOLE 0

struct BFS{
    int Y, X;
    vector<vector<int>> air, cheese; //air: 백업용, cheese: 기록용

    BFS(int y, int x){
        Y = y, X = x;
        air.resize(Y+1, vector<int>(X+1));
        cheese.resize(Y+1, vector<int>(X+1));
    }  
    bool inRange(int y, int x){ return y >= 0 && y < Y && x >= 0 && x < X; }
    bool meltHere(int y, int x){
        int count_air = 0;
        for(int d = 0; d < 4; d++){
            int ny = y + dy[d], nx = x + dx[d];
            if (!inRange(ny, nx)) continue;
            if (air[ny][nx] == AIR) count_air++;
        }
        return count_air >= 2;
    }

    int run(){

        int days = 0;
        vector<vector<int>> visited(Y+1, vector<int>(X+1));
        while(true){
            bool allMelted = true;
            bfs1();
            
            visited.clear(); 
            visited.resize(Y+1, vector<int>(X+1));
            // debugV2D(cheese);
            for(int y = 0; y < Y; y++){
                for(int x = 0; x < X; x++){
                    if (air[y][x] == CHEESE && !visited[y][x]){
                        bfs2(y, x, visited);
                        allMelted = false;
                        // debugV2D(cheese);
                    }
                }
            }

            if (allMelted) break;
            days++;
            air = cheese;
        } 
        return days;
    }
    // 처음 돌면서 가장자리 2로 바꿈
    void bfs1(int sy = 0, int sx = 0){
        vector<vector<int>> visited(Y+1, vector<int>(X+1));
        queue<P> q;
        q.push({sy, sx});
        visited[sy][sx] = true;
        cheese[sy][sx] = AIR;

        while(!q.empty()){
            auto [y, x] = q.front(); q.pop();

            for(int d = 0; d < 4; d++){
                int ny = y + dy[d], nx = x + dx[d];
                if (!inRange(ny, nx)) continue;
                if (visited[ny][nx]) continue;
                if (air[ny][nx] == CHEESE) continue;
                
                q.push({ny, nx});
                visited[ny][nx] = true;
                cheese[ny][nx] = AIR;
            }
        }
        air = cheese;
    }

    void bfs2(int sy, int sx, vector<vector<int>>& visited){
        queue<P> q;
        q.push({sy, sx});
        visited[sy][sx] = true;
        if (meltHere(sy, sx)) cheese[sy][sx] = AIR;

        while(!q.empty()){
            auto [y, x] = q.front(); q.pop();

            for(int d = 0; d < 4; d++){
                int ny = y + dy[d], nx = x + dx[d];

                if (!inRange(ny, nx)) continue;
                if (cheese[ny][nx] == AIR || cheese[ny][nx] == HOLE) continue;
                if (visited[ny][nx]) continue;
                if (meltHere(ny, nx)) cheese[ny][nx] = AIR;
                q.push({ny, nx});
                visited[ny][nx] = true;
            }
        }
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int Y, X; cin >> Y >> X;
    BFS Graph(Y, X);

    for(int y = 0; y < Y; y++)
        for(int x = 0; x < X; x++) 
            cin >> Graph.cheese[y][x];

    Graph.air = Graph.cheese;
    cout << Graph.run();
    
    return 0;
}