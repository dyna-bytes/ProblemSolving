class Solution {
public:
    int findMin(vector<int>& nums) {
        if(nums.size() == 1) return nums[0];
        
        return twoPointer(0, nums.size()-1, nums);
    }
    
    // 관찰1. Rotated Sorted Array는 두 개의 오름차순 배열로 이루어져 있다.
    // 관찰2. 첫 번째 오름차순 배열의 모든 값은 두 번째 오름차순 배열의 모든 값보다 항상 크다.
    // 관찰3. 관찰2는 오름차순 배열이 한 개 있는지, 두 개 있는지 판별하기 위해 쓸 수 있다.
    //        만약 A1.front() > A2.back() 라면 배열이 두 개, 아니라면 하나.
    
    // case1. 두 개의 오름차순 배열이 있는 경우
    // 두 번째 오름차순 배열의 시작점이 최솟값이다.
    // case2. 한 개의 오름차순 배열만이 있는 경우
    // 배열의 시작점이 최솟값이다.
    
    // s : A1의 최댓값, e : A2의 최솟값
    int twoPointer(int s, int e, vector<int>& nums){
        if(s == e) return 0;
        if(s + 1 == e) return min(nums[s], nums[e]);
        
        if(nums[s] > nums[e]){
            int mid = (s + e)/2;
            if(nums[mid] > nums[s]) return twoPointer(mid, e, nums);
            else return twoPointer(s, mid, nums);
        }
        else{
            return nums[s];
        }
    }
};