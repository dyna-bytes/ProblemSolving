class Solution {
    
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if(n == 0) return {};
        if(n == 1) return {0};
        
        vector<int> res;
        vector<int> degrees(n);
        vector<vector<int>> adj(n);
        for(vector<int> edge : edges){
            int from = edge[0], to = edge[1];
            adj[from].push_back(to);
            adj[to].push_back(from);
            degrees[from]++;
            degrees[to]++;
        }
        
        queue<int> q;
        for(int i = 0; i < n; i++) // 말단 노드를 찾는다.
            if(degrees[i] == 1) q.push(i);
        
        // level-order bfs
        while(!q.empty()){
            res.clear();
            int qsize = q.size();
            for(int i = 0; i < qsize; i++){
                int curr = q.front();
                q.pop();
                res.push_back(curr);
                
                for(int next: adj[curr]){
                    degrees[next]--;
                    if(degrees[next] == 1) q.push(next);
                }
            }
        }
        
        return res;
    }
};