class Solution {
public:
    vector<int> dp;
    int maxResult(vector<int>& nums, int k) {
        int n = nums.size();
        dp.resize(n + 1, 0);
        dp[n-1] = nums[n-1];
        
        deque<int> q; // 인덱스: 단조 감소, 배열값: 단조 감소
        q.push_back(n-1);
        
        for(int here = n-2; here >= 0; here--){
            while(!q.empty() && q.front() > min(n-1, here+k))
                q.pop_front(); // 점프할 수 없는 위치의 dp배열 인덱스
            
            dp[here] = dp[q.front()] + nums[here];
            
            while(!q.empty() && dp[q.back()] <= dp[here])
                q.pop_back();
            q.push_back(here);
        }
        
        return dp[0];
    }
    
};