class Solution {
public:
    int whatBox(int y, int x){
        y = y / 3;
        x = x / 3;
        return (y * 3) + x;
    }
        
    bool isValidSudoku(vector<vector<char>>& board) {
        unordered_set<char> rows[9], cols[9], boxes[9];
        
        for(int y = 0; y < 9; y++){
            for(int x = 0; x < 9; x++){
                char num = board[y][x];
                if(num == '.') continue;
                
                if(rows[y].find(num) != rows[y].end()) return false;
                else rows[y].insert(num);
                
                if(cols[x].find(num) != cols[x].end()) return false;
                else cols[x].insert(num);
                
                int b = whatBox(y, x);
                if(boxes[b].find(num) != boxes[b].end()) return false;
                else boxes[b].insert(num);
            }
        }
        return true;
    }
};