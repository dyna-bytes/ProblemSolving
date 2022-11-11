#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define endl '\n'
typedef long long ll;

bool cmp(pair<int, int>& a, pair<int, int>& b){
    if(a.first == b.first) return a.second > b.second;
    return a.first < b.first;
}

int N;
int MAX_ST = 1;
vector<pair<int, int>> A;
vector<int> tree;

/** @brief: 구간 최댓값을 구하는 세그먼트 트리
 * x로 끝나는 LIS 길이 = A[i] = x 인 구간 [0, i]에 지금까지 존재하는 최대 LIS 길이 + 1
 * 
 * 1. A[i] = x 값을 모두 받아 (x, i) pair로 만들고 x 값에 대해 오름차순 정렬함
 * 2. 작은 x 값부터 순회하면서,
 *   A[i] = x인 구간 [0, i]에서 최댓값을 구하고, 
 *   그 값 + 1을 인덱스 i에 해당하는 리프 노드 값으로 업데이트 한다.
 */

void update(int idx, int val){
    int curr = idx + MAX_ST/2;
    while(curr > 0){
        tree[curr] = max(val, tree[curr]);
        curr /= 2;
    }
}

int getMaxVal(int s, int e){
    int l = s + MAX_ST/2;
    int r = e + MAX_ST/2;
    int ret = 0;
    while(l <= r){
        if(l % 2) ret = max(ret, tree[l++]);
        if(!(r % 2)) ret = max(ret, tree[r--]);

        l /= 2;
        r /= 2;
    }
    return ret;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> N; A.resize(N);
    for(int i = 0; i < N; i++){
        int val; cin >> val;
        A[i] = {val, i};
    }

    sort(A.begin(), A.end(), cmp);
    while(MAX_ST < N) MAX_ST <<= 1;
    MAX_ST <<= 1;

    tree.resize(MAX_ST);
    for(pair<int, int> pair: A){
        int val = pair.first, idx = pair.second;

        int subMax = getMaxVal(0, idx);
        update(idx, subMax + 1);
    }
    cout << tree[1];
    // for(int t : tree) debug(t);

    return 0;
}