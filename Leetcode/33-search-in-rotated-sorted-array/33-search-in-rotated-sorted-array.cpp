class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        if(n == 1) return (nums[0] == target)? 0 : -1;

        int minIdx = findMinIdx(0, n-1, nums);
        if(minIdx == 0) return findTgtIdx(minIdx, n-1, nums, target);
        
        int maxIdx = minIdx - 1;
        if(nums[maxIdx] < target) return -1;
        else if(nums[0] <= target && target <= nums[maxIdx]) return findTgtIdx(0, maxIdx, nums, target);
        else if(nums[n-1] < target && target < nums[0]) return -1;
        else if(nums[minIdx] <= target && target <= nums[n-1]) return findTgtIdx(minIdx, n-1, nums, target);
        else return -1;
    }
    
    // rotated sorted array는 두 개의 오름차순 정렬된 배열로 이루어져 있다.
    // 전체 배열이 두 개의 오름차순 배열로 이루어져 있다고 하자.
    // 즉, A = [[A1], [A2]]. 이때 A1 > A2 이다.
    
    // case1. A1.back() < target                --> return -1
    // case2. A1.front() <= target <= A1.back()
    // case3. A2.back() < target < A1.front()   --> return -1
    // case4. A2.front() <= target <= A2.back()
    // case5. target < A2.front()               --> return -1
    
    // 절대 불가능한 1, 3, 5번 케이스는 제외하고
    // 2, 4번 케이스는 하나의 정렬된 어레이에서 원하는 값을 찾는 문제이다.
    // stl lower_bound를 쓰든 직접 구현하든 알아서 하면 된다.
    
    // 최솟값의 인덱스를 리턴한다.
    int findMinIdx(int s, int e, vector<int>& nums){
        if(s == e) return 0;
        if(s + 1 == e) return (nums[s] < nums[e])? s : e;
        
        if(nums[s] > nums[e]){
            int mid = (s + e)/2;
            if(nums[mid] > nums[s]) return findMinIdx(mid, e, nums);
            else return findMinIdx(s, mid, nums);
        }
        else{
            return s;
        }
    }
    
    // 구간 [s, e] 에서 타겟을 찾음
    int findTgtIdx(int s, int e, vector<int>& nums, int target){
        if(s == e) return (nums[s] == target)? s : -1;
        if(s + 1 == e){
            if(nums[s] == target) return s;
            else if(nums[e] == target) return e;
            else return -1;
        }
        
        while(s <= e){
            int mid = (s + e)/2;
            if(nums[mid] == target) return mid;
            else if(nums[mid] > target) e = mid - 1;
            else s = mid + 1;
        }
        
        if(target == nums[s]) return s;
        return -1;
    }
};