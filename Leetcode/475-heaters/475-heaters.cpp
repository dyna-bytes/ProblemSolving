class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());
        
        int n = houses.size(), m = heaters.size();
        vector<int> res(n, INT_MAX);
        
        for(int i = 0, j = 0; i < n && j < m; ){
            if(houses[i] > heaters[j]) j++;
            else {
                res[i] = heaters[j] - houses[i];
                i++;
            }
        }
        
        for(int i = n-1, j = m-1; i >= 0 && j >= 0; ){
            if(houses[i] < heaters[j]) j--;
            else {
                res[i] = min(res[i], houses[i] - heaters[j]);
                i--;
            }
        }
        
        return *max_element(res.begin(), res.end());
    }
};

// [집과 가장 가까운 히터와의 거리] 중 최댓값을 구하면, 그게 곧 히터가 모든 집을 커버할 수 있는 최소 반경이다.
// 모든 집에서 각자 자신에게 가장 가까운 히터와의 거리를 구하기 위해
// 각 집에서 오른쪽을 바라보며 가장 가까운 히터를 구하고,
// 각 집에서 왼쪽을 바라보며 가장 가까운 히터를 구한 후,
// 오른쪽으로 가까운 히터와 왼쪽으로 가까운 히터 중 더 가까운 히터와의 거리만을 저장한다.
