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

// get 2 ** N - 1
void bigIntHandler(int N) {
    long double power = 1.0;
    for (int i = 0; i < N; i++)
        power *= 2;

    char str[100000];
    sprintf(str, "%.0Lf", power);
    int len = strlen(str);
    str[len - 1] -= 1;
    // 2의 지수는 마지막자리가 0으로 끝나지 않음을 보장
    // 따라서 항상 올바르게 2 ** N - 1을 구할 수 있음
    printf("%s\n", str);
}

void Hanoi(int from, int by, int to, int N) {
    if (N == 0) return;

    Hanoi(from, to, by, N - 1);
    printf("%d %d\n", from, to);
    Hanoi(by, from, to, N - 1);
}

int main(){
    int N; 
    scanf("%d", &N);

    bigIntHandler(N);
    if (N <= 20) Hanoi(1, 2, 3, N);

    return 0;
}