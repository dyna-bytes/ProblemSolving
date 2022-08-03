class Solution {
public:
    vector<long long> dp;
    int combinationSum4(vector<int>& nums, int target) {
        if(target == 0) return 0;
        dp.resize(target+1);
        
        dp[0] = 1;
        for(int i = 1; i <= target; i++){
            for(int n : nums){
                if(i >= n && dp[i] + dp[i-n] < INT_MAX)
                    dp[i] += dp[i-n];
            }
        }
        return dp[target];
    }
    
    /*
    int f(vector<int>& nums, int target){
        int& ret = dp[target];
        if(ret) return ret;
        if(target == 0) return ret =1;
        
        for(int n : nums){
            if(target - n >= 0){
                ret += (f(nums, target - n));
            }
        }
        return ret;
    }
    */
};