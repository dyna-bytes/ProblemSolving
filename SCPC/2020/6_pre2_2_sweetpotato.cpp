#include <bits/stdc++.h>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define debugVec(v) do { \
    std::cout << "[Debug] ["; \
    for(int i = 0; i < ((v.size())-1); i++) std::cout << v[i] << "|"; \
    std::cout << v[((v.size())-1)] << "]\n"; \
} while(0)
#define debugV2D(v) do { \
    std::cout << "[Debug] [\n"; \
    for(int y = 0; y < (v.size()); y++) { \
        std::cout << "  ["; \
        for(int x = 0; x < ((v[y].size())-1); x++) \
            std::cout << v[y][x] << "|"; \
        std::cout << v[y][(v[y].size())-1] << "]\n"; \
    } \
    std::cout << "]\n"; \
} while(0)
#define endl '\n'
typedef long long ll;
typedef pair<int, int> P;

/**
 * @brief Maximum Subarray Sum with Maximum Constraint Condition
 * 
 * 1. 시간 제약 조건 때문에 O(n)에 최대 구간합 문제를 해결하는 Kadane's 알고리즘은 불가
 * 2. 연속된 최대 구간을 구해야 한다는 점에서 Prefix Sum 시도 가능
 * 3. 순진하게 구간합 배열을 선언하고, 이중 for문을 돌며 prfs[i]-prfs[j] 중 최댓값을 구하려 한다면
 *  메모리 제약에 막힘
 * 4. 즉, 구간합을 구하되 구간합배열은 선언하지 않는 트릭을 써야함.
 * 5. 입력을 받으면서 즉시 구간합을 계산하여 set에 저장해놓고, 
 *  set에서 원하는 제약 조건(현재 구간합과의 차이가 M 이하)을 만족하는 이전 구간합을 O(logn)에 꺼내서
 *  두 구간합의 차이로 연속된 최대 구간합을 매번 구해보면 된다. 총 시간복잡도는 O(nlogn).
 * 
 */
void solve(){
    int N;
    ll M; 
    cin >> N >> M;

    // pSum[i+1] = pSum[i] + A[i]
    // sum(A[a, b]) = pSum(b+1) - pSum(a)
    set<ll> s;
    s.insert(0);
    ll res = 0, pSum = 0;
    for(int i = 0; i < N; i++){
        ll A; cin >> A;
        pSum += A;
        s.insert(pSum);

        // keep sum(A[a, b]) <= M
        // filter only pSum(b+1) - pSum(a) <= M
        ll pSumBegin = *s.lower_bound(pSum - M);
        res = max(res, pSum - pSumBegin);
    }
    cout << res << endl;
};

int main(int argc, char** argv){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int T, test_case;

    cin >> T;
    for(test_case = 0; test_case  < T; test_case++){
        
        cout << "Case #" << test_case+1 << endl;
        solve();
    }

    return 0;
}