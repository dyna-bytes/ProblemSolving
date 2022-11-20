// Online C++ compiler to run C++ program online
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <tuple>
using namespace std;
typedef vector<int> vint;
#define endl '\n'

struct UnionFind {
  vint parent;
  UnionFind(int n) {
      parent.resize(n + 1, -1);
  }
  int find(int curr) {
      if (parent[curr] < 0) return curr;
      return parent[curr] = find(parent[curr]);
  }
  void merge(int from, int to) {
      from = find(from);
      to = find(to);
      if (from == to) return;
      
      parent[to] += parent[from];
      parent[from] = to;
  }
  int getSize(int curr) {
      return abs(parent[find(curr)]);
  }
};

int main() {
    int N, M; cin >> N >> M;
    UnionFind dis_set(N);
    
    for (int i = 1; i <= N; i++) {
        int size; cin >> size;
        dis_set.parent[i] = -size;
    }
    
    for (int i = 0; i < M; i++) {
        int from, to; cin >> from >> to;
        dis_set.merge(from, to);
        cout << dis_set.getSize(to) << endl;
    }
    return 0;
}