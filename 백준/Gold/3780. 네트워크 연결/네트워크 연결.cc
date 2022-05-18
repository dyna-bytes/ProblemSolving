#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define endl '\n'
typedef long long ll;

struct UnionFind{
    vector<int> parent;
    vector<int> dist; // 현재 노드부터 루트 노드까지의 경로 합
    UnionFind(int n){
        parent.resize(n+1, -1);
        dist.resize(n+1);
    }
    int find(int n){
        if(parent[n] < 0) return n;

        int root = find(parent[n]);        
        dist[n] += dist[parent[n]];
        return parent[n] = root;
    }
    void merge(int from, int to){
        int rootOfFrom = find(from);
        int rootOfTo = find(to);
        if(rootOfFrom == rootOfTo) return;

        dist[from] += abs(from - to)%1000;
        parent[from] = to;
    }
    int getDist(int n){
        find(n);
        return dist[n];
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int T; cin >> T;
    while(T--){
        int N; cin >> N;
        UnionFind uf(N);

        char op; 
        int I, J;
        while(cin >> op){
            if(op == 'O') break;
            else if(op == 'E'){
                // return dist
                cin >> I;
                cout << uf.getDist(I) << endl;
            }
            else if(op == 'I'){
                // union two sets
                cin >> I >> J;
                uf.merge(I, J);
            }
        }
    }
    
    return 0;
}