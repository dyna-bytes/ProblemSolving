#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define endl '\n'
typedef long long ll;
typedef pair<int, int> pos;
typedef pair<int, pos> node;
const int INF = 1000000000;
const int dy[] = {-1, 1, 0, 0}, dx[] = {0, 0, -1, 1};

struct Dijkstra{
    int Y, X;
    vector<vector<int>> room;
    vector<vector<int>> sum;
    Dijkstra(int y, int x){
        Y = y, X = x;
        room.resize(Y+1, vector<int>(X+1));
        sum.resize(Y+1, vector<int>(X+1, INF));
    }
    bool inRange(int y, int x){ return y >= 0 && y < Y && x >= 0 && x < X; }
    int run(){
        vector<vector<bool>> visited(Y+1, vector<bool> (X+1));
        priority_queue<node, vector<node>, greater<node>> pq;

        sum[0][0] = 0;
        pq.push({sum[0][0], {0, 0}});
        while(!pq.empty()){
            pos curr = pq.top().second; pq.pop();
            int y = curr.first, x = curr.second;

            if(visited[y][x]) continue;
            visited[y][x] = true;

            for(int d = 0; d < 4; d++){
                int ny = y + dy[d], nx = x + dx[d];
                if(!inRange(ny, nx)) continue;
                if(sum[ny][nx] > sum[y][x] + room[ny][nx]){
                    sum[ny][nx] = sum[y][x] + room[ny][nx];
                    pq.push({sum[ny][nx], {ny, nx}});
                }
            }
        }
        return sum[Y-1][X-1];
    }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int Y, X; cin >> X >> Y; // 문제의 배열을 transpose하여 사용하기로 함
    Dijkstra Graph(Y, X);

    for(int y = 0; y < Y; y++){
        string inp; cin >> inp;
        for(int x = 0; x < X; x++){
            Graph.room[y][x] = inp[x] - '0';
        }
    }
    cout << Graph.run();
    
    return 0;
}