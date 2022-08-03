class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return nums[0];
        
        vector<vector<int>> dp;
        dp.resize(n+2, vector<int>(2, 0));
        
        
        // 첫번째 집 털고, 마지막 집 안 텀
        for(int i = n-1; i >= 0; i--){
            for(int j = 0; j < 2; j++){
                if(i == n-1){ // 마지막 집 안 텀
                    dp[i][0] = 0; dp[i][1] = 0;
                    continue;
                }
                
                if(j == 0){ // 현재 집을 안 텀
                    dp[i][0] = max( dp[i+1][0], dp[i+1][1] ); // 이전 집을 안털거나, 털거나
                } else {  // 현재 집을 텀
                    dp[i][1] = nums[i] + dp[i+1][0]; // 이전 집을 안 털고 + 현재 집 돈
                }
            }
        }
        
        int ret = dp[0][1]; // 첫 번째 집 텀
        dp.clear();
        dp.resize(n+2, vector<int>(2, 0));
        
        // 첫번째 집 안 털고, 마지막 집 텀
        for(int i = n-1; i >= 0; i--){
            for(int j = 0; j < 2; j++){
                if(i == n-1){ // 마지막 집 텀
                    dp[i][0] = 0; dp[i][1] = nums[i];
                    continue;
                }
                
                if(j == 0){ // 현재 집을 안 텀
                    dp[i][0] = max( dp[i+1][0], dp[i+1][1] ); // 이전 집을 안털거나, 털거나
                } else if (i != n-2) {  // 현재 집을 텀
                    dp[i][1] = nums[i] + dp[i+1][0]; // 이전 집을 안 털고 + 현재 집 돈
                }
            }
        }
        
        ret = max(ret, dp[0][0]); // 첫 번째 집 안 텀
        dp.clear();
        dp.resize(n+2, vector<int>(2, 0));
        
        // 첫번째 집 안 털고, 마지막 집 안 텀
        for(int i = n-1; i >= 0; i--){
            for(int j = 0; j < 2; j++){
                if(i == n-1){ // 마지막 집 안 텀
                    dp[i][0] = 0; dp[i][1] = 0;
                    continue;
                }
                
                if(j == 0){ // 현재 집을 안 텀
                    dp[i][0] = max( dp[i+1][0], dp[i+1][1] ); // 이전 집을 안털거나, 털거나
                } else {  // 현재 집을 텀
                    dp[i][1] = nums[i] + dp[i+1][0]; // 이전 집을 안 털고 + 현재 집 돈
                }
            }
        }
        
        ret = max(ret, dp[0][0]);
        return ret;
    }
};