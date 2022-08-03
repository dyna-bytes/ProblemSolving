class Solution {
public:
    int minCost(string colors, vector<int>& neededTime) {
        int ret = 0;
        int sum = 0;
        int maxTime = 0;
        int n = colors.size();
        // find the start and end index of consecutive sequence
        int s = 0;
        for(int e = 0; e <= n; e++){
            if(e < n && colors[e] == colors[s]){
                sum += neededTime[e];
                maxTime = max(maxTime, neededTime[e]);
            }else{ // if consecutive sequence terminates
                if(e != s-1){
                    ret += (sum - maxTime);
                }
                if(e == n) break;
                s = e;
                sum = neededTime[s];
                maxTime = neededTime[s];
            }
        }
        return ret;
    }
};