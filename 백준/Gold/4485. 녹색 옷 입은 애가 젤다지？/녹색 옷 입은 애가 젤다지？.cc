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

const int dy[] = {-1, 1, 0, 0}, dx[] = {0, 0, -1, 1};
const int INF = 1000000000;

struct Dijkstra{
    int N;
    vector<vector<int>> cost, sum;
    Dijkstra(int n){
        N = n;
        cost.resize(N+1, vector<int>(N+1));
        sum.resize(N+1, vector<int>(N+1, INF));
    }
    bool inRange(int y, int x){ return y >= 0 && y < N && x >= 0 && x < N; }
    int run(){
        pos S = {0, 0};
        sum[S.first][S.second] = cost[S.first][S.second];

        vector<vector<int>> visited(N+1, vector<int>(N+1));
        priority_queue<node, vector<node>, greater<node>> pq;
        pq.push({sum[S.first][S.second], S});
        
        while(!pq.empty()){
            pos curr = pq.top().second; pq.pop();
            int y = curr.first, x = curr.second;

            if(visited[y][x]) continue;
            visited[y][x] = true;

            for(int d = 0; d < 4; d++){
                int ny = y + dy[d], nx = x + dx[d];
                if(!inRange(ny, nx)) continue;
                if(sum[ny][nx] > sum[y][x] + cost[ny][nx]){
                    sum[ny][nx] = sum[y][x] + cost[ny][nx];
                    pq.push({sum[ny][nx], {ny, nx}});
                }
            }
        }

        return sum[N-1][N-1];
    }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int cnt = 1;
    while(true){
        int N; cin >> N;
        if(N == 0) break;

        Dijkstra Graph(N);
        for(int y = 0; y < N; y++)
            for(int x = 0; x < N; x++)
                cin >> Graph.cost[y][x];
        
        cout << "Problem " << cnt << ": " << Graph.run() << endl;
        cnt++;
    }
    return 0;
}