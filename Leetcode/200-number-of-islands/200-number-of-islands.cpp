class Solution {
public:
    int Y, X;
    vector<vector<bool>> visited;
    int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, -1, 1};
    
    bool inRange(int y, int x){
        return (y >= 0 && y < Y && x >= 0 && x < X);
    }
    
    void dfs(int y, int x, vector<vector<char>>& grid){
        visited[y][x] = true;
        
        for(int dir = 0; dir < 4; dir++){
            int ny = y + dy[dir], nx = x + dx[dir];
            
            if(!inRange(ny, nx)) continue;
            if(visited[ny][nx]) continue;
            if(grid[ny][nx] == '1') dfs(ny, nx, grid);            
        }
    }
    
    int numIslands(vector<vector<char>>& grid) {
        Y = grid.size();
        X = grid[0].size();
        visited.resize(Y, vector<bool>(X, false));
        
        int cnt = 0;
        for(int y = 0; y < Y; y++){
            for(int x = 0; x < X; x++){
                if(!visited[y][x] && grid[y][x] == '1'){
                    dfs(y, x, grid);
                    cnt++;
                }
            }
        }
        return cnt;
    }
};