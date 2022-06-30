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
typedef tuple<int, int, int> T;

#define ROCK 0
#define FREE 1
const int dy[] = {-1, 1, 0, 0}, dx[] = {0, 0, -1, 1};

class solution {
public:
    int Y, X;
    vector<vector<int>> map, visited;
    
    bool inRange(int y, int x){ return y >= 0 && y < Y && x >= 0 && x < X; }
    // 현재 노드에서 가장 먼 노드까지 탐색함. 가장 먼 곳에 위치한 노드와 길이를 구함
    T dfs(P curr) { // Tuple <y, x, 누적 dist>
        int y = get<0>(curr), x = get<1>(curr);

        visited[y][x] = true;

        T ret = {y, x, 0};
        for(int d = 0; d < 4; d++){
            int ny = y + dy[d], nx = x + dx[d];
            if (!inRange(ny, nx)) continue;
            if (visited[ny][nx]) continue;
            if (map[ny][nx] == ROCK) continue;

            T farthest = dfs({ny, nx});
            if (get<2>(ret) < get<2>(farthest))
                ret = farthest;
        }

        get<2>(ret) += 1;
        return ret;
    }

    void solve(){
        cin >> X >> Y;
        map.resize(Y+1, vector<int>(X+1));
        visited.resize(Y+1, vector<int>(X+1));

        int sy, sx;
        for(int y = 0; y < Y; y++){
            string inp; cin >> inp;
            for(int x = 0; x < X; x++){
                if (inp[x] == '#') map[y][x] = ROCK; // rock
                else{ 
                    map[y][x] = FREE; // free space (nodes of tree)
                    sy = y, sx = x;
                }
            }
        }

        T ret1 = dfs({sy, sx});

        visited.clear(); 
        visited.resize(Y+1, vector<int>(X+1));

        T ret2 = dfs({get<0>(ret1), get<1>(ret1)});

        cout << "Maximum rope length is ";
        cout << get<2>(ret2) - 1;
        cout << "." << endl;
    };
};


int main(int argc, char** argv){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int T, test_case;

    cin >> T;
    for(test_case = 0; test_case  < T; test_case++){
        
        solution sol;
        sol.solve();
    }

    return 0;
}