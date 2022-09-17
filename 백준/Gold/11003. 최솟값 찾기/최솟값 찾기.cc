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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N, L;
    cin >> N >> L;
    vint A(N);
    for (int i = 0; i < N; i++) cin >> A[i];

    deque<pii> deq; // deq{i, A[i]}. A[i]를 단조증가꼴로 저장

    for (int i = 0; i < N; i++) {
        while (!deq.empty() && deq.back().second > A[i])
            deq.pop_back();

        deq.push_back({i, A[i]});

        while (!deq.empty() && deq.front().first < i - L + 1)
            deq.pop_front();

        cout << deq.front().second << " ";
    }
    return 0;
}