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
const int MOD = 1e6;

int N;
vint pos;
vint power;

int hanoi(int disc, int to) {
    if (disc == 0) return 0;

    int now = pos[disc];
    int sub = 3 - now - to; // now와 to가 아닌 제 3의 자리

    if (now == to) return hanoi(disc - 1, to);
    return (power[disc - 1] + hanoi(disc - 1, sub)) % MOD;
}

void square(int N) {
    power[0] = 1;
    for (int i = 1; i <= N; i++)
        power[i] = power[i - 1] * 2 % MOD;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> N;
    pos.resize(N + 1);    
    power.resize(N + 1);
    square(N);

    int num[3];
    cin >> num[0] >> num[1] >> num[2];

    int target;
    for (int n = 0; n < 3; n++) {
        for (int i = 0; i < num[n]; i++) {
            int disc; cin >> disc;
            pos[disc] = n;

            if (disc == N) target = n;
        }
    }

    cout << target + 1 << endl;
    cout << hanoi(N, target);
    return 0;
}