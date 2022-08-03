class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if(nums.size() == 0) return 0;
        
        int ret = 1;
        unordered_set<int> set;
        for(int num: nums) set.insert(num);
        
        for(int n: set){
            // if n is the start of the strick
            if(set.find(n-1) == set.end()){
                int strickEnd;
                for(strickEnd = n; set.find(strickEnd) != set.end(); strickEnd++) ;
                ret = max(ret, strickEnd - n);
            }
        }
        return ret;
    }
};

// hash에 배열값을 모두 넣고, hash에서 가장 긴 연속된 값을 찾으면 된다.