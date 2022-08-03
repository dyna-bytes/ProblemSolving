class Solution {
public:
    int Y, X;
    int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, -1, 1};
    vector<vector<bool>> visited;
    
    bool inRange(int y, int x){
        return (y >= 0 && y < Y && x >= 0 && x < X);
    }
    
    bool exist(vector<vector<char>>& board, string word) {
        Y = board.size();
        X = board[0].size();
        visited.resize(Y, vector<bool>(X, false));
        
        bool ret = false;
        for(int y = 0; y < Y; y++){
            for(int x = 0; x < X; x++){
                if(board[y][x] == word[0]){
                    ret |= dfs(y, x, 0, board, word);
                }
            }
        }
        return ret;
    }
    
    bool dfs(int y, int x, int index, vector<vector<char>>& board, string word){
        // base case
        if(index == word.size() - 1) return true;
        
        visited[y][x] = true;
        
        bool ret = false;
        for(int d = 0; d < 4; d++){
            int ny = y + dy[d], nx = x + dx[d];
            if(!inRange(ny, nx)) continue;
            if(visited[ny][nx]) continue;
            if(board[ny][nx] == word[index+1]) 
                ret |= dfs(ny, nx, index+1, board, word);
        }
        
        visited[y][x] = false;
        return ret;
    }
};