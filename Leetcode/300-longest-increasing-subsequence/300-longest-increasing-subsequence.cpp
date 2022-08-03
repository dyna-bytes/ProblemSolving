class Solution {
public:
    
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        if(n == 0) return 0;
        
        vector<int> dp(1, INT_MIN);
        int ret = 0;
        
        for(int i = 0; i < n; i++){
            if(dp.back() < nums[i]){
                dp.push_back(nums[i]);
                ret++;
            }else{
                int pos = mylower_bound(dp, nums[i]);
                dp[pos] = nums[i];
            }
        }
        return ret;
    }
    
    // 구간[lo, hi)에서 target보다 같거나 큰 최소의 값을 찾음
    int mylower_bound(vector<int>& A, int target){
        int lo = 0, hi = A.size();
        while(lo + 1 < hi){
            int mid = (lo + hi)/2;
            if(A[mid] < target) lo = mid;
            else hi = mid;
        }
        return hi;
    }
    
};