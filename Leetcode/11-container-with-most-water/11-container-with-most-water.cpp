class Solution {
public:
    int maxArea(vector<int>& height) {
        int n = height.size();
        int left = 0, right = n-1;
        int water = 0;
        
        while(left <= right){
            int h = min(height[left], height[right]);
            water = max(water, h * (right - left));
            
            if(h == height[left]) left++;
            else right--;
        }
        return water;
    }
};