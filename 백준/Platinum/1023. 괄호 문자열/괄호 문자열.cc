#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <math.h>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define endl '\n'
typedef long long ll;

ll N, K;
vector<vector<ll>> dp;
vector<char> ans;

// pos 자리 이전에 아직 닫히지 않은 여는 괄호 '('가 sole개 일 때 괄호ㄴㄴ 문자열의 개수
ll notParenString(int pos, int sole){
    ll& ret = dp[pos][sole];
    if(ret != -1) return ret;
    if(pos == N) return ret = 0;
    if(N - pos == sole) return ret = pow(2, sole) - 1;
    // 앞으로 채워야할 자리 개수와 현재까지 열어놓은 괄호 개수가 같다면 몽땅 다 닫는 경우만 아니면 됨!
    // 따라서 2**sole - 1

    // 현재 자리에 여는 괄호를 넣었을 때, 나올 수 있는 경우의 수
    ret = notParenString(pos+1, sole+1);

    // 현재 자리에 닫는 괄호를 넣었을 때, 나올 수 있는 경우의 수
    if(sole == 0) ret += pow(2, N-pos-1); 
    // 현재까지 열어둔 괄호가 0개이고, 현재 자리에 닫는 괄호를 넣었으므로
    // 그 뒤에는 무엇이 오더라도 다 괄호ㄴㄴ 문자열임. 따라서 2**(남은 자리의 수)
    else ret += notParenString(pos+1, sole-1);
    return ret;
}

/**
 * @brief 무지성함수: (((( 부터 )))) 까지 모든 경우를 생성. 괄호 문자열을 포함하여 생성함.
 * 앞에 괄호ㄴㄴ가 있을때는 뒤에 괄호 문자열이 오더라도 상관 없으므로, 앞에 괄호 ㄴㄴ가 있을 때만 사용 가능.
 * 앞에 괄호ㄴㄴ가 있는 조건: 전체 문자열의 길이가 홀수라면, 짝수 길이의 괄호 문자열이 오더라도
 * 항상 홀수 길이의 괄호ㄴㄴ 문자열이 남아 있으므로 전체 문자열에는 괄호ㄴㄴ문자열이 남아있음.
 */
void trivial(int pos, ll k){
    if(pos == N) return;
    ll pivot = pow(2, N-pos-1);
    if(k >= pivot){
        ans[pos] = ')';
        k -= pivot;
    }else ans[pos] = '(';
    trivial(pos+1, k);
}

/**
 * @brief 지성함수: 괄호ㄴㄴ문자열을 생성함.
 * pivot = 현재 자리에 '('을 썼을 때, 나올 수 있는 괄호ㄴㄴ문자열의 경우의 수
 * k >= pivot이라면 현재 자리에 ')'를 써야 함.
 * 근데 현재까지 여는 괄호가 모두 상쇄되거나 또는 닫는 괄호만 써서 sole = 0이라면
 * 위에서 현재 자리에 닫는 괄호 ')'를 써서 괄호ㄴㄴ 문자열을 이미 만들었으므로, 그 뒤에 괄호 문자열을 포함한 모든
 * 경우가 오더라도 상관 없음. 따라서 무지성 함수를 호출함. 
 */
void notTrival(int pos, int sole, ll k){
    if(pos == N) return;
    if(N-pos == sole){
        // N/2 = N-pos = sole 
        trivial(pos, k);
        return;
    }

    ll pivot = notParenString(pos+1, sole+1);
    if(k >= pivot){
        ans[pos] = ')';
        if(sole == 0) trivial(pos+1, k-pivot);
        else notTrival(pos+1, sole-1, k-pivot);
    }else{
        ans[pos] = '(';
        notTrival(pos+1, sole+1, k);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> N >> K;
    
    dp.resize(N+1, vector<ll>(N+1, -1));
    ans.resize(N+1);


    if(N%2){ // odd case
        if(K >= pow(2, N)){ cout << -1; return 0; }
        else trivial(0, K);
    }else{ // even case
        if(K >= notParenString(0, 0)){ cout << -1; return 0; }
        else notTrival(0, 0, K);
    }

    for(int i = 0; i < N; i++) cout << ans[i];
    
    return 0;
}