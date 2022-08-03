#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int N;
int time[501], res[501], indegree[501];
vector<int> adj[501];
queue<int> q;

int main(){
    cin >> N;
    for(int i = 1; i <= N; i++){
        cin >> time[i];

        while(1){
            int pre;
            cin >> pre;
            if(pre == -1) break;
            indegree[i]++;
            adj[pre].push_back(i);
        }

        // indegree = 0 (시작점) 큐에 넣어둠
        if(indegree[i] == 0){
            res[i] = time[i];
            q.push(i);
        }
    }

    // 위상 정렬
    for(int i = 1; i <= N; i++){
        int curr = q.front();
        q.pop();
        for(int next: adj[curr]){
            res[next] = max(res[next], res[curr]+time[next]);
            // (curr)->(next) 간선 삭제. 새로운 시작점 발견하면 큐에 넣음
            if(--indegree[next] == 0) q.push(next);
        }
    }

    for(int i = 1; i <= N; i++)
        cout << res[i] << "\n";
}