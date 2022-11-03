#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
const ll INF = 1e9;
ll N, K;

// 배열 A에서 num 이하인 수의 개수
ll count_under(ll num) {
    ll count = 0;
    for(ll row = 1; row <= N; row++)
        count += min(num/row, N);
    /**
     * 배열의 모든 값이 i * j [1 <= i <= N][1 <= j <= N] 꼴이므로
     * num 이하의 수의 개수는 num >= i * j 인 모든 i, j의 개수이다.
     * 따라서 가능한 i = [1, N]에 대해
     * num / i >= j 를 만족하는 j의 개수를 더하면 된다.
     * 
     * 단, num >= N*N/2 인 경우에는 (배열의 중앙값보다 큰 경우)
     * num / i >= j 인 모든 j를 찾아도 j <= N 을 넘을 수 없으므로 이 점을 유의한다.
     */
    return count;
}

int main(){
    cin >> N >> K;

    ll lo = 0, hi = min(N*N, INF);
    while(lo + 1 < hi){
        int mid = (lo + hi)/2;

        if (count_under(mid) >= K) hi = mid;
        else lo = mid;
    }

    cout << hi;
    return 0;
}