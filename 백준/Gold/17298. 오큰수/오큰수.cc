#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;
typedef vector<int> vint;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)

int N;
vint A;

void solve(int N, vint& A) {
    stack<int> S; // 내림차순 모노톤 스택
    vint ans;
    reverse(A.begin(), A.end());
    for (int a : A) {
        if (S.empty()) ans.push_back(-1);
        else if (S.top() > a) ans.push_back(S.top());
        else if (S.top() <= a) {
            while (!S.empty() && S.top() <= a) S.pop();
            if (S.empty()) ans.push_back(-1);
            else ans.push_back(S.top());
        }

        S.push(a);
    }

    reverse(ans.begin(), ans.end());
    for (int& a : ans) cout << a << " ";
}

int main() {
    FASTIO;
    cin >> N;
    A.resize(N);
    for (int& a : A) cin >> a;
    solve(N, A);
    return 0;
}