#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define FASTIO cin.tie(0)->sync_with_stdio(0)
#define MAX_M 30

int N, K, M;
vector<int> students;
vector<vector<int>> next_videos;
// next[i][j] : 정점 i 에서 2^j 번 이동한 후의 정점

void solve() {
    // next[i][j+1] = 정점 i 에서 2^(j+1) 번 이동한 후의 정점
    // next[ next[i][j] ][j] = 정점 i 에서 2^j 번 이동한 후의 정점에서 2^j 번 더 이동
    // == 2^j + 2^j == 2^(j+1)
    for (int j = 0; j < MAX_M-1; j++)
        for (int i = 1; i <= K; i++)
            next_videos[i][j+1] =
                next_videos[ next_videos[i][j] ][j];

    for (auto start_video: students) {
        int video = start_video;
        for (int i = 0; i < MAX_M; i++) {
            if ((1 << i) & (M-1))
                video = next_videos[video][i];
        }

        cout << video << " ";
    }
}

int main() {
    FASTIO;
    cin >> N >> K >> M;

    students.resize(N);
    for (auto& video: students) cin >> video;

    next_videos.resize(K + 1, vector<int>(MAX_M, 0));
    for (int i = 1; i < next_videos.size(); i++)
        cin >> next_videos[i][0];

    solve();
    return 0;
}