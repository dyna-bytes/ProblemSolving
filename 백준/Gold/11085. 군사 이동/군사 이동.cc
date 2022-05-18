#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define endl '\n'
typedef long long ll;
/**
 * @brief Haybale 문제에서 '연속된' 열에서의 최대 매운맛 중 최소 매운맛을 구하기 위해
 * 가장 덜 매운 맛부터 유니온 파인드로 양 옆의 노드를 이어붙여 나갔다.
 * 
 * 이 문제에서는 반대로 가장 넓은 길부터, 길의 양 옆 노드를 붙여나가다가
 * 시작점과 도착점이 같은 집합에 속하면 그 때의 길의 너비가 조건을 만족하는 최소 너비이다.
 * 
 * 간선을 모두 지운, 오직 노드만이 있는 그래프에서 넓은 길 부터 간선을 이어붙여 가다가
 * 시작점과 도착점이 경로 안에 포함되면 그게 시작점과 도착점을 이으며, 경로 내의 모든 간선이 
 * 최소 너비 간선보다 큰 경로가 된다.
 */

struct UnionFind{
    vector<int> parent;
    UnionFind(int n){
        parent.resize(n + 1, -1);
    }
    int find(int curr){
        if(parent[curr] < 0) return curr;
        return parent[curr] = find(parent[curr]);
    }
    void merge(int from, int to){
        from = find(from);
        to = find(to);
        if(from == to) return;

        if(abs(parent[from]) > abs(parent[to])) swap(from, to);
        parent[to] += parent[from];
        parent[from] = to;
    }
};

bool cmp(vector<int>& v1, vector<int>& v2){
    return v1[2] > v2[2]; // 오직 길의 너비만에 대해 내림차순으로 정렬
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int p, w; cin >> p >> w;
    int from, to; cin >> from >> to;

    UnionFind uf(p);
    vector<vector<int>> adj(w, vector<int>(3));
    for(int i = 0; i < w; i++)
        cin >> adj[i][0] >> adj[i][1] >> adj[i][2];

    sort(adj.begin(), adj.end(), cmp);

    for(auto adjacent: adj){
        int start = adjacent[0];
        int end = adjacent[1];
        int width = adjacent[2];

        uf.merge(start, end);
        if(uf.find(from) == uf.find(to)){
            cout << width;
            break;
        }
    }
    

    return 0;
}