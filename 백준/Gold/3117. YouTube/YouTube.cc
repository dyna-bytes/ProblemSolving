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

const ll MAX_X = 100'001;
const ll MAX_K = 30; // MAX_K >= log2(MAX_X)


int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll next[MAX_X][MAX_K]; // next[x][k] := f_2^k(x)
    // f(x) satisfies below conditions
    // 1. f(x) = f_1(x)
    // 2. f_(a+b)(x) = f_b(f_a(x))
    
    ll N, X, M;
    cin >> N >> X >> M;
    // 각 학생이 처음 본 동영상 x
    vector<ll> x_list(N);
    for (int i = 0; i < N; i++) 
        cin >> x_list[i];
    
    // x = [1, X]에 대한 f_1(x)의 값
    for (int x = 1; x <= X; x++)
        cin >> next[x][0]; // f_2^0(x) = f_1(x)

    // 희소 테이블 구축
    for (int k = 0; k < MAX_K-1; k++)
        for (int x = 1; x <= X; x++)
            next[x][k+1] = next[ next[x][k] ][k];
            // f_2^(k+1)(x) = f_2^k( f_2^k(x) )

    // 각 학생이 M-1번 이동 후에 도착한 동영상 번호
    M--;
    for (int x: x_list) {
        for (ll k = MAX_K-1; k >= 0; k--)
            if (M & (1 << k)) 
                x = next[x][k];
        cout << x << " ";
    }
    
    return 0;
}