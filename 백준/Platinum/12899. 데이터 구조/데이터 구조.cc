#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define debugPair(x)  std::cout << "[Debug] " << #x << " is {" << x.first << ", " << x.second << "}" << '\n'
#define endl '\n'
typedef long long ll;
typedef pair<int, int> P;
const int INF = 1e9 + 1;

struct SegTree{
    int size;
    vector<int> node;
    SegTree(int n){
        size = 1;
        while(size < n) size *= 2;
        size *= 2;
        node.resize(size + 1);
    }
    void insert(int idx, int val=1){
        idx += size/2 - 1; // one base leaf node index
        node[idx] += val;
        idx /= 2;
        while(idx > 0){
            node[idx] = node[idx*2] + node[idx*2 + 1];
            idx /= 2;
        }
    }
    int Kth(int k){
        int curr = 1;
        while(curr < size/2){
            if(node[curr*2] < k){
                k -= node[curr*2];
                curr *= 2;
                curr++;
            }else{
                curr *= 2;
            }
        }
        return curr - size/2;
    }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int N; cin >> N;
    SegTree tree(2'000'000);
    for(int i = 0; i < N; i++){
        int op, num;
        cin >> op >> num;
        if(op == 1) tree.insert(num);
        if(op == 2){
            int ret = tree.Kth(num);
            cout << ret + 1 << endl;
            tree.insert(ret + 1, -1);
        }
    }
    

    return 0;
}