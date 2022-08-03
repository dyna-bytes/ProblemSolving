class Solution {
public:
    string removeDigit(string number, char digit) {
        int n = number.size();
        int last_d;
        for(int p = 0; p < n; p++){
            if(p < n-1 && number[p] == digit && number[p+1] > number[p])
                return number.substr(0, p) + number.substr(p+1);
            
            if(number[p] == digit) last_d = p;
        }
        
        if(last_d == n-1) return number.substr(0, last_d);
        return number.substr(0, last_d) + number.substr(last_d+1);
    }
};