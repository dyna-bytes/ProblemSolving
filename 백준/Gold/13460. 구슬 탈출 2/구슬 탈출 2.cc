/* call by address, call by reference 차이 : 
    https://medium.com/pocs/%ED%95%A8%EC%88%98%EC%9D%98-%EC%9D%B8%EC%9E%90-%EC%A0%84%EB%8B%AC-%EB%B0%A9%EC%8B%9D-7070cdf38645
*/ 

#include<iostream>
#include<vector>
#include<queue>
using namespace std;
#define endl '\n'
#define MAX 10

typedef struct{
    int ry, rx, by, bx, cnt;
}node;

typedef struct{
    int y, x;
}pos;

typedef vector<vector<vector<vector<int> > > > 
vec_4D; // an alias for this crazy type

int Y, X;
pos hall;

const int dy[4] = { -1, 1, 0, 0 }, dx[4] = { 0, 0, -1, 1 }; /* up, down, left, right */

/* 
    미로의 모서리 만을 탐색 대상으로 삼는 BFS 문제이다.

    만약, visited[ry][rx][by][bx] 에 빨간 공과 파란 공이 돌아다니는
    모든 경로를 저장한다면
    10 * 10 * 10 * 10 = 10000 -> 2^10000 가지 경우의 수가 visited에 저장 될 수 있으므로
    큐에 너무 많은 노드가 들어가게 된다.
    또한, 이미 지나간 경로의 중간에 다시 방문하는 것이 불가능해진다.
    예를 들어, 빨간 공이 (y,x) = (0,0) -> (0,5) 로 과거에 이동한 경우
    빨간 공이 다시 (y,x) = (5,3) -> (0,3) 로 이동하는 것이 불가능하다.
    (이미 (0,3)이 방문된 상태이기 때문에.)

    따라서 미로의 모서리 만을 방문과 탐색이 가능한 노드로 삼아야
    가능한 경우의 수를 줄일 수 있고, 모서리와 모서리의 사이로
    지나간 경로의 중간에 재방문 할 수 있다.                     
*/

void Print(int ry, int rx, int by, int bx, vector<vector<char> > map){
    for(int y = 0; y < Y; y++){
            for(int x = 0; x < X; x++){
                if(y == ry && x == rx) cout << "R";
                else if(y == by && x == bx) cout << "B";
                else cout << map[y][x];
            }
            cout << endl;
        }
}

void Input(vector<vector<char> > &map, queue<node> &Q){
    pos red, blue;
    cin >> Y >> X;
    for(int y = 0; y < Y; y++){
        vector<char> X_axis;
        for(int x = 0; x < X; x++){
            char buf; cin >> buf;
            
            if(buf == 'O') hall = { y, x };
            else if(buf == 'R') red = { y, x }; 
            else if(buf == 'B') blue = { y, x };

            X_axis.push_back(buf);
        }
        map.push_back(X_axis);
    }
    Q.push({red.y, red.x, blue.y, blue.x, 0});
}

bool isHall(const pos cur_node, const vector<vector<char> > &map){
    int y = cur_node.y, x = cur_node.x;
    if(map[y][x] == 'O') return true;
    else return false;
}

bool inRange(const pos cur_node){
    int y = cur_node.y, x = cur_node.x;
    if(y < 0 || y >= Y || x < 0 || x >= X) return false;
    else return true;
}

bool isWall(const pos cur_node, const vector<vector<char> > &map){
    int y = cur_node.y, x = cur_node.x;
    if(!inRange({y, x})) return true;
    if(map[y][x] == '#') return true;
    else return false;
}

bool is_hall_in_dir(const pos cur_node, const int dir, const vector<vector<char> > &map){
    int y = cur_node.y, x = cur_node.x;
    while (!isWall({y, x}, map)){
        if(isHall({y, x}, map)) return true;

        y += dy[dir];
        x += dx[dir];        
    }
    return false;
}

pos next_node(pos node, pos avoid, int dir, vector<vector<char> > &map){
    if(isWall(node, map)) return node; 

    int y = node.y, x = node.x;
    while(!isWall({y,x}, map)){
        if(y == avoid.y && x == avoid.x) break;        

        y += dy[dir];
        x += dx[dir];
    }

    y -= dy[dir];
    x -= dx[dir];

    return {y, x};
}

int BFS(vector<vector<char> > &map, vec_4D &visited, queue<node> &Q){
    while(!Q.empty()){
        node cur_node = Q.front(); Q.pop();
        const int ry = cur_node.ry, rx = cur_node.rx;
        const int by = cur_node.by, bx = cur_node.bx;
        int t = cur_node.cnt; t++;

        visited[ry][rx][by][bx] = 1;

        // cout << "t : " << t << endl;
        // Print(ry, rx, by, bx, map);
        // cout << endl;

        if(t > 10) return -1;

        for(int dir = 0; dir < 4; dir++){
            if(is_hall_in_dir({by,bx},dir,map)) continue;
            if(is_hall_in_dir({ry,rx},dir,map)) return t;
            pos next_red, next_blue;
            switch (dir){
            case 0: // up
                if(ry <= by){
                    next_red = next_node({ry, rx}, {0, 0}, dir, map);            
                    next_blue = next_node({by, bx}, {next_red.y, next_red.x}, dir, map);
                }
                else{          
                    next_blue = next_node({by, bx}, {0, 0}, dir, map);
                    next_red = next_node({ry, rx}, {next_blue.y, next_blue.x}, dir, map); 
                }
                break;
            case 1: // down
                if(ry >= by){
                    next_red = next_node({ry, rx}, {0, 0}, dir, map);            
                    next_blue = next_node({by, bx}, {next_red.y, next_red.x}, dir, map);
                }
                else{          
                    next_blue = next_node({by, bx}, {0, 0}, dir, map);
                    next_red = next_node({ry, rx}, {next_blue.y, next_blue.x}, dir, map); 
                }
                break;
            case 2: // left
                if(rx <= bx){
                    next_red = next_node({ry, rx}, {0, 0}, dir, map);            
                    next_blue = next_node({by, bx}, {next_red.y, next_red.x}, dir, map);
                }
                else{          
                    next_blue = next_node({by, bx}, {0, 0}, dir, map);
                    next_red = next_node({ry, rx}, {next_blue.y, next_blue.x}, dir, map); 
                }
                break;
            case 3: // right
                if(rx >= bx){
                    next_red = next_node({ry, rx}, {0, 0}, dir, map);            
                    next_blue = next_node({by, bx}, {next_red.y, next_red.x}, dir, map);
                }
                else{          
                    next_blue = next_node({by, bx}, {0, 0}, dir, map);
                    next_red = next_node({ry, rx}, {next_blue.y, next_blue.x}, dir, map); 
                }
                break;
            }

            const int next_ry = next_red.y, next_rx = next_red.x;          
            const int next_by = next_blue.y, next_bx = next_blue.x;

            if(!inRange({next_ry,next_rx}) || !inRange({next_by,next_bx})) continue;
            if(isWall({next_ry,next_rx}, map) && isWall({next_by,next_bx}, map)) continue;
            if(visited[next_ry][next_rx][next_by][next_bx]) continue;

            Q.push({next_ry, next_rx, next_by, next_bx, t});

            // cout << "t : " << t << " dir : " << dir << endl;
            // cout << "(ry, rx) : (" << next_ry << ", " << next_rx << "), (by, bx) : (" << next_by << ", " << next_bx << ")" << endl;
            // Print(next_ry, next_rx, next_by, next_bx, map);
            // cout << endl;
        }
    }
    return -1;
}

int main(){
    vector<vector<char> > map;
    queue<node> Q;
    Input(map, Q);

    vec_4D visited(Y, vector<vector<vector<int> > >(X, vector<vector<int> >(Y, vector<int>(X, 0))));
    cout << BFS(map, visited, Q);
    return 0;
}