#include <iostream>
#include <vector>
using namespace std;
int N;
vector<vector<int>> dp;

// n개 성냥개비로 k자리 수를 만들 수 있는가?
int match(int n, int k){
    if(n < 0) return false;
    int& ret = dp[n][k];
    if(ret != -1) return ret;

    if(k == 1){
        return ret = (n >= 2 && n < 8);
    }
    if(k == 0){
        return ret = (n == 0);
    }

    ret = false;
    for(int i = 2; i < 8; i++){
        ret |= match(n-i, k-1);
    }
    return ret;
}

void track(int n, int k, bool firstPos = false){
    if(n == 0 || k == 0) return;
    if(!firstPos && match(n-6, k-1)){
        cout << '0';
        track(n-6, k-1);
    }else if(match(n-2, k-1)){
        cout << '1';
        track(n-2, k-1);
    }else if(match(n-5, k-1)){
        cout << '2';
        track(n-5, k-1);
    }else if(match(n-4, k-1)){
        cout << '4';
        track(n-4, k-1);
    }else if(match(n-6, k-1)){
        cout << '6';
        track(n-6, k-1);
    }else if(match(n-3, k-1)){
        cout << '7';
        track(n-3, k-1);
    }else if(match(n-7, k-1)){
        cout << '8';
        track(n-7, k-1);
    }
}

// Greedy
void getHighest(int n){
    if(n % 2){
        cout << '7';
        n -= 3;
    }

    for(; n; n -= 2) cout << '1';    
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int T; cin >> T;
    while(T--){
        cin >> N;
        int K = (N-1)/7 + 1;

        dp.clear();
        dp.resize(N+1, vector<int>(K+1, -1));
        track(N, K, true);
        cout << " ";
        getHighest(N);
        cout << endl;
    }
}