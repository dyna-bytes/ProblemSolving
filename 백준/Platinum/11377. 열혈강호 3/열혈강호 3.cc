#include <bits/stdc++.h>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define debugVec(v) do { \
    std::cout << "[Debug] ["; \
    for(int i = 0; i < ((v.size())-1); i++) std::cout << v[i] << "|"; \
    std::cout << v[((v.size())-1)] << "]\n"; \
} while(0)
#define debugV2D(v) do { \
    std::cout << "[Debug] [\n"; \
    for(int y = 0; y < (v.size()); y++) { \
        std::cout << "  ["; \
        for(int x = 0; x < ((v[y].size())-1); x++) \
            std::cout << v[y][x] << "|"; \
        std::cout << v[y][(v[y].size())-1] << "]\n"; \
    } \
    std::cout << "]\n"; \
} while(0)
#define endl '\n'
typedef long long ll;
typedef pair<int, int> P;

struct MaxMatching{
    int N, M;
    vector<int> A, B;
    vector<vector<int>> adj;
    vector<int> visited;
    MaxMatching(int n, int m){
        N = n, M = m;
        A.resize(N*2 + 1, -1), B.resize(M+1, -1);
        adj.resize(N*2 + 1);
        visited.resize(N*2 + 1);
    }
    void addAdj(int a, int b){
        adj[a].push_back(b);
    }
    bool canMatch(int a){
        if (visited[a]) return false;
        visited[a] = true;

        for(int b: adj[a]){
            if (B[b] == -1 || canMatch(B[b])) {
                A[a] = b;
                B[b] = a;
                return true;
            }
        }
        return false;
    }
    int run(bool is_Q, int K){
        int match = 0;
        for(int a = (is_Q? N:0); a < (is_Q? N*2:N); a++){
            if (A[a] == -1) {
                fill(visited.begin(), visited.end(), 0);
                if (canMatch(a)) match++;
            }
        }
        if (is_Q) return min(K, match);
        return match;
    }
};

/**
 * @brief 정점을 분리하는 이분 매칭
 * 
 * N명의 사람과 M개의 일을 매칭시킬 때 최대 몇 개의 일을 매칭시킬 수 있는지 찾는 문제.
 * N명 중 K명이 최대 2개의 일을 할 수 있는데, 그 K명이 누구인지는 상관없다.
 * 
 * 가장 처음 떠올릴 수 있는 방법은, 아무리 많이 일을 해도 최대 N+K를 넘는 일을 할 수는 없으므로
 * 열혈강호2 처럼 각 직원마다 정점을 2개로 분리하고 매칭(유량)을 세다가 N+K개가 되면 멈추는 것이다.
 * 그러나, 총 매칭이 N+K 이하이더라도 일을 2개씩 하는 직원이 K명 보다 많은 반례가 존재하므로 이는 불가능하다.
 * 
 * 각 직원을 2개의 정점으로 분할하고, 첫 번째 정점 그룹을 P, 두 번째 정점 그룹을 Q라 하자.
 * 먼저 P 그룹의 N개 정점들에 대해서만 최대 매칭을 구한다.(각 직원이 일을 하나씩만 하는 경우 발생할 수 있는 최대 매칭)
 * 그 다음, Q 그룹의 N개 정점들에 대해서 다시 최대 매칭을 구하는데, 이때 Q 그룹에서 매칭이 K개 발생하면 중단한다.
 * (최대 K명의 직원이 일을 2개씩 하는 경우)
 * 이때의 총 매칭 개수가 답이다.
 * 
 */

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N, M, K;
    cin >> N >> M >> K;

    MaxMatching Graph(N, M);
    for(int i = 0; i < N; i++){
        int cnt; cin >> cnt;
        while(cnt--){
            int job; cin >> job;
            job--;
            Graph.addAdj(i, job);
            Graph.addAdj(i+N, job);
        }
    }

    int ret = Graph.run(false, 0);
    ret += Graph.run(true, K);
    cout << ret;

    return 0;
}