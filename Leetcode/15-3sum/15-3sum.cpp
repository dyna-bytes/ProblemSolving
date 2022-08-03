class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ret;
        int n = nums.size();
        if(n < 3) return {};
        
        sort(nums.begin(), nums.end());
        
        for(int i = 0; i < n - 2; i++){
            if(i > 0 && nums[i] == nums[i-1]) continue;
            
            int l = i + 1, r = n - 1;
            while(l < r){
                int threeSum = nums[i] + nums[l] + nums[r];
                
                if(threeSum > 0) r--;
                else if(threeSum < 0) l++;
                else if(threeSum == 0){
                    ret.push_back({nums[i], nums[l], nums[r]});
                    
                    l++;
                    while(l < r && nums[l] == nums[l-1]) l++;
                    
                    r--;
                    while(l < r && nums[r] == nums[r+1]) r--;
                }
            }
        }
        return ret;
    }
};