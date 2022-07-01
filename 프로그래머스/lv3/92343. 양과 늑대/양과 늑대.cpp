#include <bits/stdc++.h>
using namespace std;

#define WOLF 1
#define SHEEP 0

vector<int> infos;
vector<int> leftChild, rightChild;
vector<int> visited(1<<17);

int N;

// 노드의 방문 순서는 양의 개수에 영향을 미치지 않는다.
// 노드의 방문 상태만이 양의 개수에 영향을 미친다.

int dfs(int state){
    if (visited[state]) return 0;
    visited[state] = true;

    int wolf = 0, nodes = 0;
    for (int i = 0; i < N; i++) {
        if (state & (1 << i)) { // 이미 탐색을 거친 노드
            nodes++;
            wolf += infos[i];
        }
    }

    if (2*wolf >= nodes) return 0; // 늑대가 절반 이상인 경우 양이 다 잡아먹힘
    int ret = nodes - wolf;

    for (int i = 0; i < N; i++) {
        if (state & (1 << i)) {
            if (leftChild[i] != -1) 
                ret = max(ret, dfs(state | 1 << leftChild[i]));
            if (rightChild[i] != -1) 
                ret = max(ret, dfs(state | 1 << rightChild[i]));
        }
    }
    return ret;
}

int solution(vector<int> info, vector<vector<int>> edges) {
    N = info.size();
    leftChild.resize(N, -1);
    rightChild.resize(N, -1);

    for(auto vint: edges){
        int p = vint[0], c = vint[1];
        if (leftChild[p] == -1) leftChild[p] = c;
        else rightChild[p] = c;
    }

    infos = info;

    return dfs(1);
}
