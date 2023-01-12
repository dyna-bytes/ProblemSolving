#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define debug(x) cout << "[debug] " << (#x) << " is " << (x) << endl;
#define debugIter(v) do{\
    cout << "[debug] " << #v << endl;\
    for (auto e: v) cout << e << " | ";\
    cout << endl;\
}while(0);
typedef pair<int, int> pii;
typedef vector<int> vint;
typedef vector<pii> vpii;
const int MAX = 100;
const int LEN = 10;

int N;
int paper[MAX][MAX];

void input() {
    auto fill_paper = [&](int sy, int sx) {
        for (int y = sy; y < sy + LEN; y++)
            for (int x = sx; x < sx + LEN; x++)
                paper[y][x] = 1;
    };

    cin >> N;
    int y, x;
    for (int i = 0; i < N; i++) {
        cin >> y >> x;
        fill_paper(y, x);
    }
}

// 계단식으로 구간합 전처리
void preprocess() {
    for (int y = 1; y < MAX; y++)
        for (int x = 0; x < MAX; x++)
            if (paper[y][x] == 1) paper[y][x] = paper[y-1][x] + 1;
            // paper[y][x] means height from {y0, x} to {y, x} where paper[y0][x] == 0
}

int solve() {
    int max_area = 0;
    for (int y = 0; y < MAX; y++) {
        for (int sx = 0; sx < MAX; sx++) {
            int h = MAX;
            for (int ex = sx; ex < MAX; ex++) {
                h = min(h, paper[y][ex]);
                
                if (h == 0) break;
                max_area = max(max_area, h * (ex - sx + 1));
            }
        }
    }
    return max_area;
}
int main() {
    FASTIO;
    input();
    preprocess();
    cout << solve();

    return 0;
}