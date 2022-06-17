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

class solve{
public:
    ll lineSweeping(int n, vector<P>& arr){
        sort(arr.begin(), arr.end());
        
        ll ret = 0;
        int l = -INF, r = -INF;
        for(P line: arr){
            if(r < line.first){
                ret += (r - l);
                l = line.first;
                r = line.second;
            }else
                r = max(r, line.second);
        }

        ret += (r - l);
        return ret;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int N;
    cin >> N;

    vector<P> arr(N);
    for(int i = 0; i < N; i++)
        cin >> arr[i].first >> arr[i].second;

    solve sol;
    cout << sol.lineSweeping(N, arr);
    
    return 0;
}