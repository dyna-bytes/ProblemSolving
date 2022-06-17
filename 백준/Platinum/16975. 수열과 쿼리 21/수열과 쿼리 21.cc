#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define endl '\n'
typedef long long ll;

struct SegTree{
    int size;
    vector<ll> node;
    SegTree(int n){
        size = 1;
        while(size < n) size *= 2;
        size *= 2;
        node.resize(size);
    }
    void insert(int idx, int val){
        idx += size/2;
        node[idx] += val;
        idx /= 2;
        while(idx > 0){
            node[idx] = node[idx*2] + node[idx*2 + 1];
            idx /= 2;
        }
    }
    // 구간 [s, e]의 합을 구함
    ll sum(int s, int e){
        int l = s + size/2;
        int r = e + size/2;
        ll ret = 0;
        while(l <= r){
            if(l % 2) ret += node[l++];
            if(!(r % 2)) ret += node[r--];
            l /= 2;
            r /= 2;
        }
        return ret;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N; cin >> N;
    vector<ll> arr(N+1); // one base index
    for(int i = 1; i <= N; i++) cin >> arr[i];

    SegTree tree(N+1);

    int M; cin >> M;
    for(int i = 0; i < M; i++){
        int op; cin >> op;
        if(op == 1){
            int start, end, val;
            cin >> start >> end >> val;
            // 세그트리에 증감의 변화량 만을 기록함
            tree.insert(start, val);
            tree.insert(end + 1, -val);
        }else{
            int get;
            cin >> get;
            // 범위[1, get] 내의 변화량을 모두 더한 뒤, 원래의 배열값과 합침
            cout << tree.sum(1, get) + arr[get] << endl;
        }
    }
    return 0;
}