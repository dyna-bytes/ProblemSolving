class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int n = fruits.size();
        if(n == 1) return 1;
        
        map<int, int> basket;
        int ret = 0;
        for(int start = 0, end = 0; end < n; end++){
            basket[fruits[end]]++;
            
            if(basket.size() > 2){
                if(--basket[fruits[start]] == 0) basket.erase(fruits[start]);
                
                start++;
            }
            
            ret = end - start + 1; // 얘 자체가 max갱신을 포함하고 있음
            // 값이 커졌으면 커졌지 작아지진 않음
        }
        
        return ret;
    }
};
/*
* end가 과일을 담고, start가 end를 뒤따라가며 과일을 버림.
* start가 지나간 후의 과일은 다 버려진다.
* start가 과일을 버리는 조건 : 바스킷에 과일이 3종류 이상.
*/