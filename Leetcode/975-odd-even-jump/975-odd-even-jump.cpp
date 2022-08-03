/*
lower_bound, upper_bound 설명
https://blockdmask.tistory.com/168
*/
class Solution {
public:
    int oddEvenJumps(vector<int>& arr) {
        int n = arr.size();
        vector<bool> oddJumpFrom(n, false); // A[n] 보다 큰 값 중 최솟값으로 이동
        vector<bool> evenJumpFrom(n, false);// A[n] 보다 작은 값 중 최댓값으로 이동
        
        oddJumpFrom[n-1] = true;
        evenJumpFrom[n-1] = true;
        
        map<int, int> map; // <element, index>
        map[arr[n-1]] = n-1;
        
        int ret = 1;
        for(int i = n-2; i >= 0; i--){
            auto greater = map.lower_bound(arr[i]); // arr[i]보다 크거나 같은 값
            auto smaller = map.upper_bound(arr[i]); // arr[i]보다 큰 값
            // smaller--; // arr[i]보다 작거나 같은 값
            
            if(greater != map.end())
                oddJumpFrom[i] = evenJumpFrom[greater->second];
            if(smaller != map.begin())
                evenJumpFrom[i] = oddJumpFrom[(--smaller)->second];
            
            if(oddJumpFrom[i]) ret++;
            map[arr[i]] = i;
        }
        return ret;
    }
};