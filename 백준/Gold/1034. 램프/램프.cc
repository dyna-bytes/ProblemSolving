#include <bits/stdc++.h>
#define FASTIO cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(0)
#define endl '\n'
using namespace std;

int Y, X;
vector<string> lamps;
int K;

void input() {
    cin >> Y >> X;
    lamps.resize(Y);

    for (int y = 0; y < Y; y++)
        cin >> lamps[y];

    cin >> K;
}

int solve() {
    int ans = 0;

    // 각 row 마다 꺼진 램프의 개수를 셈
    for (int y = 0; y < Y; y++) {
        int off_count = 0;

        for (int x = 0; x < X; x++) {
            if (lamps[y][x] == '0')
                off_count++;
        }

        // off_count 만큼 꺼진 램프를 켤 때
        // 남은 toggle 횟수 (K - off_count) 가 even 이라면,
        // 이미 켜진 램프의 수를 유지할 것임.
        int same = 0;
        if ((K >= off_count) && ((K - off_count) % 2 == 0)) {
            for (int _y = y; _y < Y; _y++) {
                if (lamps[_y] == lamps[y])
                    same++;

                ans = max(ans, same);
            }
        }
    }

    return ans;
}

int main() {
    FASTIO;
    input();
    cout << solve();
    return 0;
}