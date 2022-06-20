#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define endl '\n'
typedef long long ll;
typedef pair<int, int> P;
const int INF = 1e9 + 1;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N, M; cin >> N >> M; // N: 사람 수, M: 강의 길이
    
    vector<P> reverse;
    for(int i = 0; i < N; i++){
        int from, to; cin >> from >> to;
        if(from < to) continue;

        reverse.push_back({to, from});
    }

    sort(reverse.begin(), reverse.end());

    int l = -INF, r = -INF;
    ll ret = 0;
    for(P line: reverse){
        if(r < line.first){
            ret += (r - l);

            l = line.first;
            r = line.second;
        }else
            r = max(r, line.second);
    }
    ret += (r - l);

    ret *= 2;
    ret += M;
    cout << ret;

    return 0;
}