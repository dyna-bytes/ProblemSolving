class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if(intervals.size() == 0) return {{}};
        
        vector<vector<int>> ret;
        sort(intervals.begin(), intervals.end());
        
        int prev_start = intervals[0][0];
        int prev_end = intervals[0][1];
        ret.push_back({prev_start, prev_end});
        
        for(int i = 1; i < intervals.size(); i++){
            int start = intervals[i][0], end = intervals[i][1];
            
            if(start <= prev_end){
                ret.back()[1] = max(prev_end, end);
            }
            else{
                ret.push_back({start, end});
            }
            prev_end = max(prev_end, end);
        }
        return ret;
    }
};