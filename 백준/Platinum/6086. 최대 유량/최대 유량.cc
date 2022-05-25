#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define endl '\n'
typedef long long ll;

const int MAX_V = 52;
const int INF = 1000000000;

// output: 0~51
inline int ctoi(char c){
    if(c <= 'Z') return c - 'A';
    return c - 'a' + 26;
}

struct NetFlow{
    int c[MAX_V][MAX_V] = {0}; // c[from][to]: from->to로 가는 간선의 용량
    int f[MAX_V][MAX_V] = {0}; // f[from][to]: from->to로 현재 흐르는 유량
    vector<int> adj[MAX_V]; // 인접 리스트

    int run(){
        //total: 총 유량, S: 소스, E: 싱크
        int total = 0, S = ctoi('A'), E = ctoi('Z');

        while(true){ // 증가 경로를 더 이상 못 찾을 때까지 루프
            //증가 경로를 BFS로 찾음
            int prev[MAX_V]; // prev[curr] = -1: 아직 현재 노드를 방문하지 않음
            fill(prev, prev+MAX_V, -1);
            queue<int> q;
            q.push(S);

            while(!q.empty()){
                int curr = q.front(); q.pop();
                // 싱크에 방문하였다면 종료
                if(prev[E] != -1) break;
                
                for(int next: adj[curr]){
                    // 1. capa > flow: 아직 유량을 흘릴 여유가 남았는가?
                    // 2. prev[next] == -1: next 정점을 아직 방문하지 않았는가?
                    if(c[curr][next] - f[curr][next] > 0 && prev[next] == -1){
                        q.push(next);
                        prev[next] = curr; // 경로는 덧씌워져도 상관없음. S->E로 가기만 하면 어떠한 경로든 상관없기 때문
                        if(next == E) break; // 싱크에 도달하였다면 종료
                    }
                }
            }
            // 싱크로 가는 증가 경로가 더이상 없다면 루프 탈출
            if(prev[E] == -1) break;

            // 경로 상에서 가장 허용치가 낮은 곳(blocking edge)를 찾음
            int flow = INF;
            for(int node = E; node != S; node = prev[node])
                flow = min(flow, c[prev[node]][node] - f[prev[node]][node]);
            
            // 찾은 flow만큼 해당 경로에 유량 흘려줌
            for(int node = E; node != S; node = prev[node]){
                f[prev[node]][node] += flow;
                f[node][prev[node]] -= flow;
            }
             
            // 총 유량 값 증가
            total += flow;
        }
        return total;
    }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N; cin >> N;

    NetFlow Graph;
    for(int i = 0; i < N; i++){
        char u, v; 
        int width;
        cin >> u >> v >> width;

        u = ctoi(u); v = ctoi(v);
        Graph.c[u][v] = Graph.c[v][u] += width;
        Graph.adj[u].push_back(v);
        Graph.adj[v].push_back(u);
    }

    cout << Graph.run();
    
    return 0;
}