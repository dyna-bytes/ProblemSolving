"11"~"26" 사이의 문자 "ab"는 숫자 ab로 해석되거나, a 그리고 b로 해석될 수 있다
따라서 해당 범위의 문자가 나오면 두 경우를 모두 고려해야한다.
​
문자 "10", "20"은 반드시 10, 20 으로만 해석된다.
​
f(string s){
if(s.size() == 1) return s[0] != '0' // '0' 문자열은 존재하지 않는다.
string subStr = s.substr(0, 2);
int num = stoi(subStr);
if(num == 10 || num == 20) return f(s.substr(2));
ret = f(s.substr(1));
if(num >= 11 && num <= 26) ret += f(s.substr(2))
return ret;
}