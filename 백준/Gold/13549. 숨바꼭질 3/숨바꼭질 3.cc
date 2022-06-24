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
const int MAX = 100000;

struct BFS_01{
    vector<int> visited;
    vector<int> time;
    BFS_01(){
        visited.resize(MAX+1);
        time.resize(MAX+1);
    }
    int run(int N, int K){
        deque<int> dq;
        dq.push_back(N);
        visited[N] = true;

        while(!dq.empty()){
            int curr = dq.front();
            dq.pop_front();

            if (curr == K) return time[K];
            
            // jump to curr * 2
            if (curr*2 <= MAX && !visited[curr*2]) {
                dq.push_front(curr*2);
                visited[curr*2] = true;
                time[curr*2] = time[curr];
            }
            // walk to curr - 1
            if (curr > 0 && !visited[curr-1]) {
                dq.push_back(curr-1);
                visited[curr-1] = true;
                time[curr-1] = time[curr] + 1;
            }
            // walk to curr + 1
            if (curr < MAX && !visited[curr+1]) {
                dq.push_back(curr+1);
                visited[curr+1] = true;
                time[curr+1] = time[curr] + 1;
            }
        }

        return -1;
    }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int N, K; cin >> N >> K;

    BFS_01 bfs;
    cout << bfs.run(N, K);
    
    return 0;
}