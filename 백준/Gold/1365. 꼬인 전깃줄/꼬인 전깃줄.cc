#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <climits>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define endl '\n'
typedef long long ll;

int N;
int MAX_ST = 1;
vector<pair<int, int>> A;
vector<int> tree;

bool cmp(pair<int, int>& a, pair<int, int>& b){
    if(a.first == b.first) return a.second > b.second;
    return a.first < b.first;
}

void update(int idx, int val){
    int curr = idx + MAX_ST/2;
    while(curr > 0){
        tree[curr] = max(val, tree[curr]);
        curr /= 2;
    }
}

int getMaxVal(int rangeL, int rangeR, int nodeNum, int nodeL, int nodeR){
    if(rangeL > nodeR || rangeR < nodeL) return 0;
    if(rangeL <= nodeL && nodeR <= rangeR) return tree[nodeNum];
    int mid = (nodeL + nodeR)/2;
    return max(getMaxVal(rangeL, rangeR, nodeNum*2, nodeL, mid),
                getMaxVal(rangeL, rangeR, nodeNum*2+1, mid+1, nodeR));
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> N;

    while(MAX_ST < N) MAX_ST <<= 1;
    MAX_ST <<= 1;

    tree.resize(MAX_ST, 0);
    A.resize(N);
    for(int i = 0; i < N; i++){
        int val; cin >> val;
        A[i] = {val, i};
    }
    sort(A.begin(), A.end(), cmp);

    for(pair<int, int> p : A){
        int idx = p.second;
        int submax = getMaxVal(0, idx, 1, 0, MAX_ST/2-1);
        update(idx, submax + 1);

        // debug(submax);
        // for(int t:tree) debug(t);
    }
    
    cout << N - tree[1];
    
    return 0;
}