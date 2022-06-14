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
    
    int N;
    cin >> N;
    vector<P> lines(N);

    for(int i = 0; i < N; i++)
        cin >> lines[i].first >> lines[i].second;

    sort(lines.begin(), lines.end());
    // [l, r] : 현재 합치고 있는 구간
    int res = 0, l = -INF, r = -INF;
    for(int i = 0; i < N; i++){
        // 아예 새로운 선분을 만나면
        if(r < lines[i].first){
            // 이전 선분의 길이를 더하고
            res += (r - l);

            // 현재의 새로운 선분의 왼쪽 끝과 오른쪽 끝을 기억한다.
            l = lines[i].first;
            r = lines[i].second;
        }else 
            r = max(r, lines[i].second);
            // 연속된 선분인 경우, 오른쪽 끝만 계속 늘려간다.
    }
    res += (r - l); // 마지막 선분까지 더해줌.
    cout << res;

    return 0;
}