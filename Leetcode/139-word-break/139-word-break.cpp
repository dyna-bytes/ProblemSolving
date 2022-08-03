class Solution {
public:    
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();
        vector<bool> dp(n+1); // dp[n] : n번째 char까지 wordBreak를 만족하는가
        
        for(int i = 0; i < n; i++){
            string curr_s = s.substr(i); // [i, end)까지의 문자열
            
            for(string word: wordDict){
                int len = word.size();
                if(curr_s.size() < len) continue;
                
                if(curr_s.substr(0, len) == word){
                    if(i == 0) dp[i] = true;
                    if(dp[i] == true) dp[i+len] = true;
                }
            }
        }
        
        return dp[n];
    }
    \
};