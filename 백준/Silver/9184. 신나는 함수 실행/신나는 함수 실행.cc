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

const int OFFSET = 50;
int memo[OFFSET * 2 + 1][OFFSET * 2 + 1][OFFSET * 2 + 1];

int w(int a, int b, int c) {

    int& ret = memo[a + OFFSET][b + OFFSET][c + OFFSET];
    if (ret) return ret;

    if (a <= 0 || b <= 0 || c <= 0) return ret = 1;
    else if (a > 20 || b > 20 || c > 20) return ret = w(20, 20, 20);
    else if (a < b && b < c) return ret = w(a, b, c-1) + w(a, b-1, c-1) - w(a, b-1, c);
    else return ret = w(a-1, b, c) + w(a-1, b-1, c) + w(a-1, b, c-1) - w(a-1, b-1, c-1);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int a = 0, b = 0, c = 0;
    while (true) {
        cin >> a >> b >> c;
        if (a == -1 && b == -1 && c == -1) break;
        int res = w(a, b, c);
        cout << "w(" << a << ", " << b << ", " << c << ") = " << res << endl;
    }
    return 0;
}