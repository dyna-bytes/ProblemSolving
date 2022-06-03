#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <map>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define endl '\n'
typedef long long ll;
typedef pair<int, int> p;
typedef vector<p> v;
typedef vector<vector<p>> v2;
typedef vector<vector<vector<p>>> v3;

v ans;
// p1 = here, p2 = another, p3 = there
// t: p의 n번째 블록 아래가 홀수인가?
void f(int n, int p1, int p2, int p3, int t1, int t2, int t3){
    // p1에 있는 n번째 블록을 p3로 옮기는 문제
    if(n == 0) return;
    if(n == 1){
        ans.push_back({p1, p3});
        return;
    }
    if(t1 == t3){ // 만약 p1과 p3의 홀짝성이 같다면 n번째 블록과 그 위로의 블록이 뒤집히는 일 없이 그대로 옮겨진다.
        f(n-1, p1, p3, p2, !t1, t3, t2); // n-1번째부터 위로의 블록들을 p2로 치운다. 이때 n-1번째 블록 입장에서는 p1의 홀짝성이 반대로 보인다.
        ans.push_back({p1, p3});
        f(n-1, p2, p1, p3, t2, t1, !t3); // p2로 치워둔 블록을 p3로 가져온다. 역시 p3의 홀짝성이 반전되어 보인다.
    }else{ // p1과 p3의 홀짝성이 다르다면 n번째 블록과 n-1번째 블록이 뒤집혀지고, 그 위로도 줄줄이 뒤집어진다.
        f(n-2, p1, p3, p2, t1, t3, t2); // n번째, n-1번째 블록을 동시에 옮기므로, n-2번째 블록부터 그 위로 모든 블록들을 p2로 치운다.
        ans.push_back({p1, p3}); 
        ans.push_back({p1, p3});
        f(n-2, p2, p1, p3, t2, t1, t3); // p2로 치워든 블록을 p3로 가져온다. (n, n-1)을 동시에 움직였으므로 홀짝성은 보존된다.
    }
}

void f000(int n, int p1, int p2, int p3);
void rev_f000(int n, int p1, int p2, int p3);
void f100(int n, int p1, int p2, int p3);
void rev_f100(int n, int p1, int p2, int p3);
void f001(int n, int p1, int p2, int p3);
void rev_f001(int n, int p1, int p2, int p3);

void f000(int n, int p1, int p2, int p3){
    if(n == 0) return;
    f100(n-1, p1, p3, p2); // p1의 홀짝성 반전
    ans.push_back({p1, p3});
    rev_f100(n-1, p2, p1, p3); // p3의 홀짝성 반전
}

void f100(int n, int p1, int p2, int p3){
    if(n == 0) return;
    if(n == 1){
        ans.push_back({p1, p3});
        return;
    }
    f100(n-2, p1, p3, p2); // p1의 홀짝성 보존
    ans.push_back({p1, p3});
    ans.push_back({p1, p3});
    rev_f000(n-2, p2, p1, p3); // p3의 홀짝성 보존
}

void rev_f100(int n, int p1, int p2, int p3){
    if(n == 0) return;
    if(n == 1){
        ans.push_back({p1, p3});
        return;
    }
    rev_f000(n-2, p1, p3, p2);
    ans.push_back({p1, p3});
    ans.push_back({p1, p3});
    rev_f100(n-2, p2, p1, p3);
}

void rev_f000(int n, int p1, int p2, int p3){
    if(n == 0) return;
    if(n == 1){
        ans.push_back({p1, p3});
        return;
    }
    if(n == 2){
        ans.push_back({p1, p2});
        ans.push_back({p1, p3});
        ans.push_back({p2, p3});
        return;
    }
    f001(n-1, p1, p3, p2); // p1의 홀짝성 보존
    if(n%4 < 2) ans.push_back({p1, p3});
    else        ans.push_back({p3, p1});
    rev_f001(n-1, p2, p1, p3); // p3의 홀짝성 보존
}

void f001(int n, int p1, int p2, int p3){
    if(n == 0) return;
    if(n == 1){
        ans.push_back({p1, p2});
        ans.push_back({p1, p3});
        return;
    }
    if(n == 2){
        ans.push_back({p1, p3});
        ans.push_back({p1, p2});
        ans.push_back({p1, p3});
        return;
    }
    rev_f000(n-2, p1, p2, p3);
    ans.push_back({p1, p2});
    ans.push_back({p1, p2});
    rev_f000(n-3, p3, p1, p2);
    ans.push_back({p1, p3});
    f001(n-2, p2, p1, p3);
}

void rev_f001(int n, int p1, int p2, int p3){
    if(n == 0) return;
    if(n == 1){
        ans.push_back({p1, p3});
        ans.push_back({p2, p3});
        return;
    }
    if(n == 2){
        ans.push_back({p1, p3});
        ans.push_back({p2, p3});
        ans.push_back({p1, p3});
        return;
    }
    rev_f001(n-2, p1, p3, p2);
    ans.push_back({p1, p3});
    rev_f000(n-3, p2, p3, p1);
    ans.push_back({p2, p3});
    ans.push_back({p2, p3});
    rev_f000(n-2, p1, p2, p3);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N; cin >> N;
    // f(N, 1, 2, 3, 0, 0, 0);
    f000(N, 1, 2, 3);
    cout << ans.size() << endl;
    for(p pair: ans){
        cout << pair.first << " " << pair.second << endl;
    }
    return 0;
}