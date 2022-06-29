#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

string to_K_number(int N, int K){
    if(N == 0) return "";

    string ret = to_K_number(N/K, K);
    ret.push_back(N%K + '0');
    return ret;
}

bool isPrime(ll num){
    if (num == 2LL) return true;
    if (num <= 1LL) return false;

    ll sqrt = 2;
    while (sqrt * sqrt <= num) {
        if (num % sqrt == 0) return false;
        sqrt++;
    }
    return true;
}

int solution(int n, int k) {
    int answer = 0;
    string K_num = to_K_number(n, k);
    
    ll s = 0, e = 0;
    for (; e < K_num.size(); e++) {
        if (s >= e) continue;
        if (K_num[e] == '0') {
            ll num = stoll(K_num.substr(s, e-s)); // [문자열 시작 위치, 길이]
            if (isPrime(num)) answer++;

            while (e+1 < K_num.size() && K_num[e+1] == '0') e++; // 겹쳐있는 0을 건너뜀
            s = e + 1;
        }
    }

    if (s < K_num.size() && e <= K_num.size()) {
        ll num = stoll(K_num.substr(s, e-s)); // [문자열 시작 위치, 길이]
        if (isPrime(num)) answer++;
    }

    return answer;
}
