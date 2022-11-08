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

// string 을 대상으로 하는 BFS
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int N, K;
    
    cin >> N >> K;
    string start = "", dest = "";

    for(int i = 0; i < N; i++){
        int inp; cin >> inp;
        start += inp + '0';
    }

    int ans = 0;
    dest = start;
    sort(dest.begin(), dest.end());

    unordered_set<string> visited;
    queue<string> q;

    q.push(start);
    visited.insert(start);

    int qsize = 0;
    while (!q.empty()) {
        qsize = q.size();

        for (int i = 0; i < qsize; i++) {
            string curr = q.front();
            q.pop();

            if (curr == dest) {
                cout << ans << endl;
                return 0;
            }

            for (int j = 0; j <= N - K; j++){
                string rev = curr.substr(j, K);
                reverse(rev.begin(), rev.end());

                string str = curr.substr(0, j) + rev + curr.substr(j+K, N-j-K);
                if (visited.count(str)) continue;

                visited.insert(str);
                q.push(str);             
            }
        }

        ans++;
    }
    
    cout << -1 << endl;
    return 0;
}