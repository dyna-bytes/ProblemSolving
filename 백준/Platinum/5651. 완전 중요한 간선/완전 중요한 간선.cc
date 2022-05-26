#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <climits>
#include <unordered_set>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define endl '\n'
typedef long long ll;

struct Edge{
    int to, c, f;
    Edge* dual;
    Edge(int to1, int c1){
        to = to1, c = c1, f = 0;
        dual = nullptr;
    }
    int residual(){
        return c - f;
    }
    void addFlow(int f1){
        f += f1;
        dual->f -= f1;
    }
    void subCap(){
        c--;
        dual->c++;
    }
};

struct NetworkFlow{
    int N;
    vector<vector<Edge*>> adj;
    NetworkFlow(int n){
        N = n;
        adj.resize(N+1);
    }
    void addEdge(int from, int to, int cap){
        Edge* e1 = new Edge(to, cap);
        Edge* e2 = new Edge(from, 0);
        e1->dual = e2;
        e2->dual = e1;
        adj[from].push_back(e1);
        adj[to].push_back(e2);
    }
    // Edge* findSaturationEdges(){
    //     for(vector<Edge*> vec: adj){
    //         for(Edge* e: vec){
    //             if(e->residual() == 0){
    //                 return e;
    //             }
    //         }
    //     }
    //     return nullptr;
    // }
    int run(int start, int end){
        int total = 0, S = start, E = end;
        while(true){               
            vector<int> prev(N+1, -1);
            vector<Edge*> path(N+1);
            queue<int> q;
            q.push(S);

            while(!q.empty()){
                int curr = q.front(); q.pop();
                if(curr == E) break;

                for(Edge* curr2next: adj[curr]){
                    int next = curr2next->to;
                    if(prev[next] != -1) continue;
                    if(curr2next->residual() > 0){
                        prev[next] = curr;
                        path[next] = curr2next;
                        q.push(next);

                        if(next == E) break;
                    }
                }
            }

            if(prev[E] == -1) return {};

            int flow = INT_MAX;
            for(int node = E; node != S; node = prev[node])
                flow = min(flow, path[node]->residual());
            for(int node = E; node != S; node = prev[node])
                path[node]->addFlow(flow);
            // debug(flow);
            
            total += flow;
        }
        return total;
    }

    int getCount(){
        int count = 0;
        // 어떤 간선을 잡고 그 시작점에서 유량을 흘려 반대편 끝 점에
        // 도달할 수 없으면 중요한 간선이다.
        for(int source = 1; source <= N; source++){
            for(Edge* e: adj[source]){
                if(e->c == 0 || e->residual() != 0) continue;

                int sink = e->to;

                vector<int> prev(N+1, -1);
                queue<int> q;
                q.push(source);

                while(!q.empty()){
                    int curr = q.front(); q.pop();
                    if(prev[sink] != -1) break;

                    for(Edge* edge: adj[curr]){
                        int next = edge->to;
                        if(prev[next] != -1) continue;
                        if(edge->residual() > 0){
                            prev[next] = curr;
                            q.push(next);

                            if(next == sink) break;
                        }
                    }
                }
                if(prev[sink] == -1) count++;
            }
        }
        return count;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int T; cin >> T;
    while(T--){
        int N, M; cin >> N >> M;
        NetworkFlow Graph(N);

        for(int i = 0; i < M; i++){
            int from, to, cap;
            cin >> from >> to >> cap;
            Graph.addEdge(from, to, cap);
        }

        auto ret = Graph.run(1, N);
        cout << Graph.getCount() << endl;       
        
    }
    
    return 0;
}