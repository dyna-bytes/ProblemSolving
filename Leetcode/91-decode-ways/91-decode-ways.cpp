class Solution {
public:
    vector<int> dp;
    int numDecodings(string s) {
        if(s.size() == 1 && (s[0] == '0')) return 0;
        
        dp.resize(s.size() + 1, -1);
        return decodeWays(s, 0);
    }
    
    int decodeWays(string s, int i){
        int& ret = dp[i];
        if(ret != -1) return ret;
        if(i == s.size()) return ret = 1;        
        if(s[i] == '0') return ret = 0;
        
        string subStr = s.substr(i, 2);
        int num = stoi(subStr);
        
        if(num == 10 || num == 20) 
            return ret = decodeWays(s, i+2);
        
        ret = decodeWays(s, i+1);
        if(num >= 11 && num <= 26)
            ret += decodeWays(s, i+2);
        return ret;
    }
    
};