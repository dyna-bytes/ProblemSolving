class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        int n = intervals.size();
        if(n == 0) return {newInterval};
        
        int ns = newInterval[0], ne = newInterval[1];
        
        bool catched_ns = false;
        bool catched_ne = false;
        int ns_idx = 0; // ns 삽입 인덱스
        int ne_idx = 0; // ne 삽입 인덱스
        
        for(int i = 0; i < n; i++){
            int s = intervals[i][0], e = intervals[i][1];
            if(s <= ns && ns <= e){
                catched_ns = true;
                ns_idx = i;
            }
            else if(!catched_ns && ns > e){ // 놓치고 현재 범위보다 뒤에 ns가 있다면
                ns_idx = i + 1; // 뒤의 위치를 삽입 인덱스로 지정
            }
            
            if(s <= ne && ne <= e){ 
                catched_ne = true;
                ne_idx = i + 1;
            }
            else if(!catched_ne && ne > e){
                ne_idx = i + 1;
            }
        }
        
        if(catched_ns)
            newInterval[0] = intervals[ns_idx][0];
        if(catched_ne)
            newInterval[1] = intervals[ne_idx - 1][1];
            
        // 구간 [s, e)
        auto begin = intervals.begin();
        intervals.erase(begin + ns_idx, begin + ne_idx);
        intervals.insert(begin + ns_idx, newInterval);
        return intervals;
    }
};