#include <bits/stdc++.h>
using namespace std;
#define FASTIO cin.tie(0)->sync_with_stdio(0)
typedef long long ll;

ll solve(ll A, ll B) {
    unordered_map<ll, bool> visited;
    queue<ll> q;
    
    q.push(A);
    visited[A] = true;
    
    for (int step = 1; !q.empty(); step++) {
        for (int k = q.size(); k > 0; k--) {
            auto curr = q.front();
            q.pop();
            
            if (curr == B)
                return step;
            
            ll next = curr * 2;
            if (!visited[next] && next <= B) {
                q.push(next);
                visited[next] = true;
            }
            
            next = curr * 10 + 1;
            if (!visited[next] && next <= B) {
                q.push(next);
                visited[next] = true;
            }
        }
    }
    return -1;
}

int main() {
    FASTIO;
    ll A, B;
    cin >> A >> B;
    cout << solve(A, B);
}