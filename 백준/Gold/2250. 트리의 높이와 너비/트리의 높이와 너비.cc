#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define MAX 987654321
#define MIN -MAX

int N;
vector<int> parent, leftChildren, rightChildren;
vector<int> pos;
int dp[10001];

// 서브트리의 넓이 == 서브트리에 속한 노드의 개수
int getNodes(int root){
    if(root == -1) return 0;
    if(dp[root]) return dp[root];

    int nodes = 1;

    if(leftChildren[root] != -1) nodes += getNodes(leftChildren[root]);
    if(rightChildren[root] != -1) nodes += getNodes(rightChildren[root]);
    
    return dp[root] = nodes;
}

// if 부모 노드에서 오른쪽으로 이동, 
// 자식 노드의 좌표 = 부모 노드의 좌표 + 자식의 왼쪽 서브트리의 크기
// if 부모 노드에서 왼쪽으로 이동,
// 자식 노드의 좌표 = 부모 노드의 좌표 - 자식의 오른쪽 서브트리의 크기

// 1번 노드의 x좌표를 원점으로 가정.
// 탑다운으로 내려가며 노드의 x좌표를 계산함
void setNodes(int root, bool isLeft){
    if(root == -1) return;
    
    if(isLeft)
        pos[root] = pos[parent[root]] - getNodes(rightChildren[root]) - 1;
    else
        pos[root] = pos[parent[root]] + getNodes(leftChildren[root]) + 1;

    if(leftChildren[root] != -1) setNodes(leftChildren[root], true);
    if(rightChildren[root] != -1) setNodes(rightChildren[root], false);
}

// BFS를 돌려 레벨 순회를 하고, 가장 긴 너비의 레벨을 반환한다.
void bfs(int start){
    queue<int> Q;
    Q.push(start);
    int level = 1;
    int width = 1;
    int answer_level = 1;

    while(!Q.empty()){
        int qSize = Q.size();
        int L = MAX, R = MIN;
        level++;
        for(int i = 0; i < qSize; i++){
            int curr = Q.front(); Q.pop();

            int lc = leftChildren[curr];
            int rc = rightChildren[curr];
            if(lc != -1) {
                L = min(L, pos[lc]); 
                R = max(R, pos[lc]);
                Q.push(lc);
            }
            if(rc != -1) {
                L = min(L, pos[rc]);
                R = max(R, pos[rc]); 
                Q.push(rc);
            }           
        }
        // cout << level << " : " << R - L + 1 << endl;
        if((width < R - L + 1) && (R != L)){
            answer_level = level;
            width = R - L + 1;
        }
    }
    cout << answer_level << " " << width;
}

int main(){
    cin >> N;

    parent.resize(N + 2);
    leftChildren.resize(N + 2);
    rightChildren.resize(N + 2);
    pos.resize(N + 2);

    for(int i = 1; i <= N; i++){
        int curr, lc, rc;
        cin >> curr >> lc >> rc;
        
        if(lc != -1) parent[lc] = curr;
        if(rc != -1) parent[rc] = curr;
        leftChildren[curr] = lc;
        rightChildren[curr] = rc;
    }

    // 루트 노드 찾기
    int root = N;
    while(parent[root]) root = parent[root];

    setNodes(leftChildren[root], true);
    setNodes(rightChildren[root], false);

    bfs(root);

    return 0;
}