class Solution {
public:
    vector<vector<int>> dp;
    int rob(vector<int>& nums) {
        int n = nums.size();
        dp.resize(n+2, vector<int>(2, 0));
        
        dp[0][false] = 0;
        dp[0][true] = nums[0];
        
        for(int here = 1; here < n; here++){
            int prev = here - 1;
            dp[here][true] = dp[prev][false] + nums[here];
            dp[here][false] = max(dp[prev][false], dp[prev][true]);
        }
        
        return max(dp[n-1][true], dp[n-1][false]);
    }
};