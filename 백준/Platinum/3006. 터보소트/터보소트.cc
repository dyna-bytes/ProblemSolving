#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define endl '\n'
#define even(x) ((x % 2) == 0)
typedef long long ll;

// 세그트리 구간합 연습

struct SegTree{
    int N;
    int SIZE = 1; // N보다 같거나 큰 2의 제곱수
    vector<int> tree;
    SegTree(int n){
        N = n;
        while(SIZE < N) SIZE *= 2;
        tree.resize(SIZE*2 + 1);
        init();
    }
    
    void init(){
        for(int i = SIZE*2; i >= SIZE; i--)
            tree[i] = 1;

        for(int i = SIZE - 1; i >= 1; i--)
            tree[i] = tree[2*i] + tree[2*i + 1];
    }
    
    void update(int idx, int val){
        idx = idx + SIZE;
        tree[idx] = val;
        idx /= 2;

        while(idx > 0){
            tree[idx] = tree[2*idx] + tree[2*idx + 1];
            idx /= 2;
        }
    }
    
    int sum(int s, int e){
        s = s + SIZE;
        e = e + SIZE;
        int ret = 0;
        while(s <= e){
            if(s % 2) ret += tree[s++];
            if(!(e % 2)) ret += tree[e--];
            s /= 2;
            e /= 2;
        }
        return ret;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N; cin >> N;
    vector<int> index(N+1);
    SegTree segTree(N);

    for(int i = 0; i < N; i++){
        int n; cin >> n;
        index[n] = i;
    }

    for(int cnt = 1; cnt <= N; cnt++){
        if(even(cnt)){ // 짝수 번째
            int n = N + 1 - cnt/2;
            segTree.update(index[n], 0);
            cout << segTree.sum(index[n], N-1) << endl;
        }
        else{ // 홀수 번째
            int n = 1 + cnt/2;
            segTree.update(index[n], 0);
            cout << segTree.sum(0, index[n]) << endl;
        }
    }
    return 0;
}