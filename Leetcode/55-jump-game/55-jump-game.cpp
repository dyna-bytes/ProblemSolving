class Solution {
public:
    vector<int> dp;
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        
        int push = 0;
        for(int here = 0; here < n && here <= push; here++){
            push = max(push, here + nums[here]);
        }
        return push >= n-1;
    }
};
