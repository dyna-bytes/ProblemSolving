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
        if(v[y].empty()){ std::cout << "  []\n"; continue; } \
        std::cout << "  ["; \
        for(int x = 0; x < ((v[y].size())-1); x++) \
            std::cout << v[y][x] << "|"; \
        std::cout << v[y][(v[y].size())-1] << "]\n"; \
    } \
    std::cout << "]\n"; \
} while(0)
#define endl '\n'
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vint;
typedef vector<pii> vpii;

int N;
vint weights;
vector<vint> visited;
int offset = 0;

int f(int n, int w) {
    if (w == offset) return true; // 음의 무게도 핸들링 하기 위해 offset 사용
    if (n >= N) return false;

    int& ret = visited[n][w];
    if (ret != -1) return ret;
    
    ret = f(n+1, w); // 아무런 추도 올려놓지 않기
    ret = max(ret, f(n+1, w + weights[n])); // 구슬과 같은 쪽에 추 올리기
    ret = max(ret, f(n+1, w - weights[n])); // 구슬과 반대 쪽에 추 올리기
    return ret;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> N;
    weights.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> weights[i];
        offset += weights[i];
    }

    visited.resize(N+1, vint(2*offset + 40001, -1));

    int Q; cin >> Q;
    for (int i = 0; i < Q; i++) {
        int w; cin >> w;
        if (f(0, offset + w)) cout << "Y";
        else cout << "N";
        if (i != Q) cout << " ";
    }
    return 0;
}