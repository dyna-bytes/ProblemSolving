#include <bits/stdc++.h>
using namespace std;
#define debug(curr)  std::cout << "[Debug] " << #curr << " is " << curr << '\n'
#define debugVec(v) do { \
    std::cout << "[Debug] ["; \
    for(int i = 0; i < ((v.size())-1); i++) std::cout << v[i] << "|"; \
    std::cout << v[((v.size())-1)] << "]\n"; \
} while(0)
#define debugV2D(v) do { \
    std::cout << "[Debug] [\n"; \
    for(int y = 0; y < (v.size()); y++) { \
        std::cout << "  ["; \
        for(int curr = 0; curr < ((v[y].size())-1); curr++) \
            std::cout << v[y][curr] << "|"; \
        std::cout << v[y][(v[y].size())-1] << "]\n"; \
    } \
    std::cout << "]\n"; \
} while(0)
#define endl '\n'
typedef long long ll;
typedef pair<int, int> P;
const int MAX = 100000;

struct BFS{
    int shortest = INT_MAX;
    int methods = 0;
    vector<int> time;
    vector<int> visited;
    BFS(){
        time.resize(MAX+1);
        visited.resize(MAX+1);
    }
    void run(int S, int E){
        queue<P> q;
        q.push({S, 0});
        visited[S] = true;

        while(!q.empty()){
            auto [curr, count] = q.front(); q.pop();

            visited[curr] = true;

            if (shortest < count) break;
            if (curr == E) {
                shortest = count;
                methods++;
                continue;
            }

            if (curr*2 <= MAX && !visited[curr*2])
                q.push({curr*2, count+1});
            if (curr > 0 && !visited[curr-1])
                q.push({curr-1, count+1});
            if (curr < MAX && !visited[curr+1])
                q.push({curr+1, count+1});
        }

        cout << shortest << endl;
        cout << methods;
    }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int N, K;
    cin >> N >> K;
    BFS Graph;
    Graph.run(N, K);
    
    return 0;
}