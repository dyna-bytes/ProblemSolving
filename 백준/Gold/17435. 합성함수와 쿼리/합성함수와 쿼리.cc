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

const int MAX = 500'001;
const int MAX_K = 19; // 2^k >= MAX 를 만족하는 최소 k

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int M;
    // vector<vector<int>> next(MAX, vector<int>(MAX_K));
    int next[MAX][MAX_K];

    cin >> M;
    for (int x = 1; x <= M; x++)
        cin >> next[x][0]; // f1(x) = next[x][0]

    // 희소 테이블 채우기
    // next[x][k]: f(x)의 2^k번 이동 후인 f_2^k(x)의 값
    // f_2^(k+1)(x) = f_2^k( f_2^k(x) )
    // next[x][k+1] = next[ next[x][k] ][k]
    // x에서 2^(k+1)번 이동한 후의 정점 = x에서 2^k번*2번 이동한 후의 정점
    for (int k = 1; k < MAX_K; k++)
        for (int x = 1; x <= M; x++)
            next[x][k] = next[ next[x][k-1] ][k-1];

    // 쿼리 처리
    int Q;
    cin >> Q;
    for (int i = 0; i < Q; i++) {
        int n, x;
        cin >> n >> x;
        // 켜져 있는 비트에 해당하는 배열만 사용해서 희소테이블을 건너뛴다.
        for (int k = MAX_K-1; k >= 0; k--) {
            if (n & (1 << k)) 
                x = next[x][k];
        }
        cout << x << endl;
    }
    return 0;
}