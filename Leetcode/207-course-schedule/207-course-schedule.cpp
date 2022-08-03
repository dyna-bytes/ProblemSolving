class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        int n = numCourses;
        vector<vector<int>> adj(n+1);
        vector<int> indegree(n+1);
        
        for(vector<int> edge: prerequisites){
            int from = edge[1];
            int to = edge[0];
            
            adj[from].push_back(to);
            indegree[to]++;
        }
        
        queue<int> q;
        for(int i = 0; i < n; i++)
            if(indegree[i] == 0) q.push(i);
        
        int cnt = 0;
        while(!q.empty()){
            int curr = q.front(); q.pop();
            
            for(int next: adj[curr])
                if(--indegree[next] == 0) q.push(next);
            cnt++;
        }
        return cnt == n;
    }
};

/*
//bfs
큐에 시작점(indegree = 0인 노드)인 노드를 전부 넣어놓음
for(int i = 0; i < n; i++)
    if(indegree[i] == 0) q.push(i);

cnt = 0;
while(true){
  if(q.size() == 0) return -1;
  if(q.size() >= 2) // 위상정렬 결과가 두 개 이상일 수도 있음
  
  visted[curr] = true;
  curr = q.front(); q.pop();
  
  for(next : adj[curr]){
    if(visted[next]) continue;
    
    indegree[next]--;  // (curr)->(next)
    if(indegree[next] == 0) q.push(next)
  }
}

return cnt == n?


*/