class Solution {
public:
    vector<int> dp;
    
    int minDominoRotations(vector<int>& tops, vector<int>& bottoms) {
        int N = tops.size();
        
        dp.resize(N+1, -1);        
        vector<int> t = tops, b = bottoms;
        int retTB = flip(0, t[0], t, b); // target at T[0], flip B
        
        dp.clear(); dp.resize(N+1, -1); 
        t = tops, b = bottoms;
        int retBB = flip(0, b[0], t, b); // target at B[0], flip if target == B[i]
        
        dp.clear(); dp.resize(N+1, -1); 
        t = tops, b = bottoms;
        int retBT = flip(0, b[0], b, t); // target at B[0], flip if target == T[i]
        
        dp.clear(); dp.resize(N+1, -1); 
        t = tops, b = bottoms;
        int retTT = flip(0, t[0], b, t); // target at T[0], flip if target == T[i]
        
        int ret = min(retTB, retBB);
        ret = min(ret, min(retBT, retTT));
        if(ret == INT_MAX) ret = -1;
        return ret;
    }
    
    int flip(int n, int target, vector<int>& t, vector<int>& b){
        int& ret = dp[n];
        if(ret != -1) return ret;
        if(n == t.size()) return ret = 0;
     
        if(t[n] == target) {
            return ret = flip(n+1, target, t, b);
        }
        else if(b[n] == target){
            swap(t[n], b[n]);
            ret = flip(n+1, target, t, b);
            return (ret == INT_MAX)? INT_MAX : 1 + ret;
        }
        else
            return ret = INT_MAX;
    }
};
