class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        int MAX = target + 1;
        unordered_map<string, int> m;
        vector<int> ret(2);
        
        for(int i = 0; i < n; i++){
            if(m.find(to_string(nums[i])) != m.end()){
                ret[0] = m[to_string(nums[i])];
                ret[1] = i;
                break;
            }
            else{
                m[to_string(target - nums[i])] = i;
            }
        }
        
        return ret;
    }
};