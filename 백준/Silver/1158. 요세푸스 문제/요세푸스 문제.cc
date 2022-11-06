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

int print_count = 0;
void print(int ans, int N) {
    if (print_count == 0) cout << "<" << ans << ", ";
    else if (print_count == N-1) cout << ans << ">";
    else cout << ans << ", ";

    print_count++;
}

void solve(int N, int K) {
    list<int> lst;
    for (int i = 1; i <= N; i++) {
        lst.push_back(i);
    }

    auto next = [&](auto it) {
        if (it == lst.end()) it = lst.begin();
        it++;
        if (it == lst.end()) it = lst.begin();
        return it;
    };

    int cnt = 0;
    auto it = lst.begin();
    while (!lst.empty()) {
        if (cnt < K - 1) {
            it = next(it);
            cnt++;
        }
        else {
            print(*it, N);
            it = lst.erase(it);
            cnt = 0;
        }
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N, K;
    cin >> N >> K;
    if (N == 1) {
        cout << "<1>";
        return 0;
    }

    solve(N, K);
    return 0;
}