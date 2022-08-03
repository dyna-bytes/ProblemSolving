class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        int ret = nums[0];
        int l = 1, r = 1;
        
        for(int i = 0; i < n; i++){
            l = (l == 0)? 1 : l;
            r = (r == 0)? 1 : r;
            
            l *= nums[i]; // prefix product
            r *= nums[n-i-1]; // postfix product
            ret = max(ret, max(l, r));
        }
        return ret;
    }
};