1. top down
​
dp[n-1] = nums[n-1] // 뒤에서부터 거꾸로 돌면서 배열 시작점까지 훑음
​
int maxResult(here){
if(here == -1) return 0;
for(there = 1; there <= k; there++)
if(here + there < n)
ret = max(ret, nums[here] + maxResult(there);
return ret;
}
​
2. bottom up
​
dp[0] = nums[0]
for(here = 1; here < n; here++)
for(jump = 1; jump <= k && jump <= here; jump++)
there = here - jump
dp[here] = max(dp[here], dp[there] + nums[here]) // there에서 here로 점프함
​
​
3. Optimized DP
​
dp[0] = nums[0]
set.insert(dp[0])
​
for(here = 1; here < n; here++)
if(here > k) set.erase(set.find(dp[here - k - 1])) // 거리 차이가 k+1 이상 나는 곳에서는 점프할 수 없다.
dp[here] = rbegin(set) + nums[here] // 최대 점수가 있는 위치부터 here까지 점프함
​
return dp[n-1]
​
4. Montotonic Queue Optimized DP
​
dp[0] = nums[0]
deque<int> deq{0}; // 인덱스는 단조 증가, 배열값은 단조 감소하게 담아 놓음
for(here = 1; here < n; here++)
if(deq.front() < here - k) deq.pop_front()
dp[here] = dp[deq.front()] + nums[here] // 최대 점수가 있는 위치부터 here까지 점프
while(!deq.empty() && dp[deq.back()] <= dp[here])
deq.pop_back();
deq.push_back(here);
return dp[n-1]
​