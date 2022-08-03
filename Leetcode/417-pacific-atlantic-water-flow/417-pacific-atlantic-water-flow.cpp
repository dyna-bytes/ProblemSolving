class Solution {
public:
    int Y, X;
    
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        vector<vector<int>> ret;
        Y = heights.size();
        X = heights[0].size();
      
        set<pair<int, int>> pacific, atlantic;
        
        for(int y = 0; y < Y; y++)
            BFS(y, 0, heights, pacific);
        for(int x = 0; x < X; x++)
            BFS(0, x, heights, pacific);
        for(int y = 0; y < Y; y++)
            BFS(y, X-1, heights, atlantic);
        for(int x = 0; x < X; x++)
            BFS(Y-1, x, heights, atlantic);
        
        set<pair<int, int>> intersect;
        set_intersection(pacific.begin(), pacific.end(), atlantic.begin(), atlantic.end(),
                 std::inserter(intersect, intersect.begin()));
        
        for(pair<int, int> pos : intersect){
            ret.push_back({pos.first, pos.second});
        }
        return ret;
    }
    
    bool inRange(int y, int x){
        return (y >= 0 && y < Y && x >= 0 && x < X);
    }
    
    void BFS(int sy, int sx, vector<vector<int>>& heights, set<pair<int, int>>& visited){
        const int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, -1, 1};
        
        queue<pair<int, int>> q;
        q.push({sy, sx});
        visited.insert({sy, sx});
        
        while(!q.empty()){
            pair<int, int> curr = q.front(); q.pop();
            int y = curr.first, x = curr.second;
            
            for(int d = 0; d < 4; d++){
                int ny = y + dy[d], nx = x + dx[d];
                
                if(!inRange(ny, nx)) continue;
                if(visited.find({ny, nx}) != visited.end()) continue;
                if(heights[y][x] > heights[ny][nx]) continue;
                
                visited.insert({ny, nx});
                q.push({ny, nx});
            }
        }
    }
};