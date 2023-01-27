#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;
#define MAX 50

const int dy[] = { -1, 0, 1, 0 }, dx[] = { 0, 1, 0, -1 };
typedef struct{
    int y, x;
}pos;

int N, L, R;
int visited[MAX][MAX];

void Print(vector<vector<int> > &vec2D){
    for(int y = 0; y < N; ++y){
        for(int x = 0; x < N; ++x)
            cout << vec2D[y][x] << " ";
        cout << endl;
    }
}

void Input(vector<vector<int> > &map){
    cin >> N >> L >> R;
    map = vector<vector<int> > (N, vector<int> (N, 0));

    for(int y = 0; y < N; ++y)
        for(int x = 0; x < N; ++x)
            cin >> map[y][x];
}

bool inRange(const int y, const int x){
    if(y < 0 || y >= N || x < 0 || x >= N) return false;
    else return true;
}

bool isOpenable(const int y, const int x, const int ny, const int nx, const vector<vector<int> > &map){
    if(abs(map[ny][nx] - map[y][x]) >= L && abs(map[ny][nx] - map[y][x]) <= R) return true;
    else return false;
}

bool isTrivialCase(const int y, const int x, const vector<vector<int> >&map){
    bool isTrivial = true;
    for(int d = 0; d < 4; ++d){
        int ny = y + dy[d], nx = x + dx[d];
        if(!inRange(ny, nx))                    continue;
        else if(visited[ny][nx])                continue;
        else if(!isOpenable(y, x, ny, nx, map)) continue;

        isTrivial = false;
    }
    return isTrivial;
}

// run BFS
// return the topmost and rightmost position
pos runBFS(const int y, const int x, vector<vector<int> > &map, int idx, vector<int> &unions){
    pos rightMostPos = {y, x};
    int sumPopulation = 0;
    int sumArea = 0;
    bool BFSworked = false;
    
    
    visited[y][x] = idx;
    sumPopulation += map[y][x];
    sumArea++;

    if(isTrivialCase(y, x, map)){
        unions[idx] = sumPopulation;
        return { -1, -1 };
    }

    queue<pos> Q;
    Q.push({y, x});

    while (!Q.empty()){
        pos curPos = Q.front(); Q.pop();
        const int y = curPos.y, x = curPos.x;

        if(rightMostPos.y > y){
            rightMostPos = {y, x};
        }
        else if(rightMostPos.y == y){
            if(rightMostPos.x < x)
                rightMostPos = {y, x};
        }

        for(int d = 0; d < 4; ++d){
            int ny = y + dy[d], nx = x + dx[d];
            if(!inRange(ny, nx))                    continue;
            else if(visited[ny][nx])                continue;
            else if(!isOpenable(y, x, ny, nx, map)) continue;

            Q.push({ny, nx});
            visited[ny][nx] = idx;
            sumPopulation += map[ny][nx];
            sumArea++;

            BFSworked = true;
        }
    }

    unions[idx] = sumPopulation / sumArea;

    // cout << "new pop >> " << endl;
    // cout << unions.back() << endl;
    // cout << "map >> " << endl;
    // Print(map);
    // cout << "visited >> " << endl;
    // Print(visited);
    // cout << "inserted (" << y << ", " << x << ")" << endl;
    // cout << "returned (" << rightMostPos.y << ", " << rightMostPos.x << ")" << endl;

    if(!BFSworked) return { -1, -1 };
    else           return rightMostPos;
}

bool movePopulation(vector<vector<int> > &map){
    int idx = 0;
    bool BFSworked = false;
    vector<int> unions(1, 0);
    memset(visited, 0, sizeof(visited));

    for(int y = 0; y < N; ++y)
        for(int x = 0; x < N; ++x)
            if(!visited[y][x]){
                unions.push_back(0);
                // run BFS
                pos nextPos = runBFS(y, x, map,  ++idx, unions);
                // cout << "idx : " << idx << endl;
                if(nextPos.y == -1 && nextPos.x == -1){
                    continue;
                }
                
                BFSworked = true;
                y = nextPos.y;
                x = nextPos.x;
            }
    
    
    // cout << "visited >> " << endl;
    // Print(visited);
    

    if(!BFSworked) return false;

    for(int y = 0; y < N; ++y)
        for(int x = 0; x < N; ++x)
            if(visited[y][x])
                map[y][x] = unions[visited[y][x]];

    // cout << "map >> " << endl;
    // Print(map);

    return true;
}

int main(){
    vector<vector<int> > map, visited;
    int cnt = 0;

    Input(map);
    bool moved = true;


    while(moved){
        moved = movePopulation(map);
        if(moved) ++cnt;
    }
    cout << cnt;

    return 0;
}