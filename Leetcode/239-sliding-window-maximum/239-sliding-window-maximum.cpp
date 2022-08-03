class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> deq;
        vector<int> ret;
        int n = nums.size();
        
        // 앞의 k - 1개 항을 전처리
        for(int curr = 0; curr < k - 1; curr++){
            while(!deq.empty() && nums[deq.back()] < nums[curr])
                deq.pop_back();
            deq.push_back(curr);
        }
        
        for(int curr = k - 1; curr < n; curr++){
            if(!deq.empty() && deq.front() == curr - k)
                deq.pop_front(); // deq 사이즈를 최대 k 이하로 관리
            
            while(!deq.empty() && nums[deq.back()] < nums[curr])
                deq.pop_back();
            deq.push_back(curr);
            
            ret.push_back(nums[deq.front()]);
        }
        
        return ret;
    }
};
