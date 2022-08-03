class Solution {
public:
    typedef pair<int, int> pos;
    typedef pair<int, pos> P;
    const int dy[2] = {1, 0}, dx[2] = {0, 1}; // bottom, right
    int minPathSum(vector<vector<int>>& grid) {
        Y = grid.size(), X = grid[0].size();
        vector<vector<int>> dp(Y, vector<int>(X));
        
        dp[0][0] = grid[0][0];
        for(int y = 1; y < Y; y++)
            dp[y][0] = dp[y-1][0] + grid[y][0];
        for(int x = 1; x < X; x++)
            dp[0][x] = dp[0][x-1] + grid[0][x];
        
        for(int y = 1; y < Y; y++){
            for(int x = 1; x < X; x++){
                dp[y][x] = min(dp[y-1][x], dp[y][x-1]) + grid[y][x];
            }
        }
        return dp[Y-1][X-1];
    }
private:
    int Y, X;
    bool inRange(int y, int x){ return y >= 0 && y < Y && x >= 0 && x < X; }
};