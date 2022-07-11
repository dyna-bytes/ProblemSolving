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
 * @brief multiset을 이용해 파티션을 지정하는 중앙값 찾기 문제
 * 
 * 보따리가 하나 있고 거기에 K개의 수열이 예쁘게 정렬되어 있다고 하자.
 * 이때 floor((K+1)/2)의 위치에 있는 중앙값을 찾는 것은 아주 쉬운 일이다.
 * 
 * 만약 K가 홀수 일 때, (K+1)/2 의 위치에 있는 중앙값을 기준으로 중앙값보다 작은 항들이 모두 중앙값 왼쪽에, 
 * 중앙값보다 큰 항들이 모두 중앙값 오른쪽에 위치한다면 꼭 보따리가 예쁘게 정렬되어 있지 않아도 역시 중앙값을 어렵지 않게 찾을 수 있을 것이다.
 * 그냥 가운데 있는 항을 고르면 중앙값일 테니까.
 * 
 * 즉, 우리가 할 것은 중앙값을 '파티션 바로 다음 위치의 항'으로 생각하고 보따리를 이등분 하는 파티션을 잘 설정해 주는 것이다.
 * 
 * 처음에는 K개의 수열을 보따리에 오름차순 정렬되게 넣어놓고, 파티션을 가장 오른쪽부터 왼쪽으로 이동하며 파티션 왼쪽에 (K-1)/2개의 항, 
 * 파티션 오른쪽에 (K+1)/2개의 항이 오도록 하면 된다.
 * 그러면 파티션 바로 다음 위치의 항이 곧 중앙값이 된다.
 * 
 * 그 다음부터는 i = K+1부터 N까지 A[i - K]항을 보따리에서 꺼내고 A[i]항을 보따리에 집어넣으며 파티션 위치를 정해주는 과정을 반복하면 된다.
 * 정렬된 보따리에서 항들이 제거되고 삽입되며 파티션의 위치가 불균형해졌으므로, 우선 파티션을 오른쪽으로 옮기며 파티션 왼쪽의 크기가 파티션 오른쪽의 크기보다
 * 같거나 커질 때 까지 파티션 오른쪽에서 작은 값들을 파티션 왼쪽으로 옮긴다.
 * 이때, 왜 파티션을 맨 오른쪽 끝까지 옮기지 않나면 이미 파티션 오른쪽의 대부분의 항은 파티션 왼쪽의 항들보다 크고, 기껏해야 최대 한 항 정도(오른쪽에서 최소 항이었던 A[i-K]항이 제거되고
 * 파티션 왼쪽에 중앙값보다 큰 A[i]항이 삽입된 경우) 만이 왼쪽의 최대 항보다 작기 때문이다. 즉, 파티션 오른쪽에 파티션 왼쪽보다 작은 항들이 남아있을 불상사는 고려하지 하지 않아도 된다.
 * 
 * 원래 있어야 할 위치보다 오른쪽으로 최대 한 칸(이전에 있던 직전 위치보다는 최대 두 칸) 옮겨진 파티션을 다시 왼쪽으로 옮기며 이번에는 위와 반대로
 * 중앙값보다 큰 항들을 파티션 왼쪽에서 오른쪽으로 보낸다.
 * 
 * 이 과정을 거친 후 파티션 바로 다음 위치의 항이 곧 중앙값이 된다.
 */
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int N, K; cin >> N >> K;
    
    vector<int> A(N);
    for (int i = 0; i < N; i++) 
        cin >> A[i];

    multiset<int, greater<int>> lo; // 내림차순
    multiset<int> hi; // 오름차순

    for (int i = 0; i < K; i++)
        lo.insert(A[i]); // 일단 K개의 초항들을 lo에 넣어둠

    ll sum = 0; // 중앙값의 조건: lo.size < hi.size 을 만족하기 위해
    while (lo.size() >= hi.size()) { // K개의 항을 절반씩 나눔.
        hi.insert(*lo.begin()); // lo에서 가장 큰 값을 찾아 hi로 옮김
        lo.erase(lo.begin());
    }
    sum += *hi.begin(); // 이때 hi에서 가장 작은 값이 곧 중앙값임

    for (int i = K; i < N; i++) {
        // 길이가 K인 연속 부분 수열의 조건을 유지하기 위해 K번 째 이전의 항을 찾아서 지움
        if (lo.find(A[i - K]) != lo.end()) lo.erase(lo.find(A[i - K]));
        else hi.erase(hi.find(A[i - K]));

        hi.insert(A[i]); // 현재 항 A[i]는 lo에 넣든 hi에 넣든 큰 상관 없다. 어차피 아래 과정에서 올바른 위치로 옮겨질것.

        while (lo.size() < hi.size()) { // 우선 lo.size >= hi.size가 될 때 까지
            lo.insert(*hi.begin()); // hi에서 가장 작은 값들을 lo로 옮김
            hi.erase(hi.begin());
        }
        while (lo.size() >= hi.size()) { // 다시 lo.size < hi.size를 만족하도록
            hi.insert(*lo.begin()); // lo에서 가장 큰 값들을 hi로 옮김
            lo.erase(lo.begin());
        }
        // 왜 첫 번째 while문을 먼저 수행하고 두 번째 while문을 수행하냐면,
        // 그렇게 해야 모든 원소들을 올바른 위치로 옮긴 후에 lo.size < hi.size의 조건을 유지하기 때문임.

        sum += *hi.begin();
    }
    cout << sum;
    
    return 0;
}