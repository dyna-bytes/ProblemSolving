#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define FASTIO cin.tie(0)->sync_with_stdio(0)

#define endl '\n'
// #define DEBUG
#ifdef DEBUG
#define debug(x) cout << #x << " is " << x << endl;
#define debugVect(v) do { \
    cout << #v << " is |" ; \
    for (auto i : v) cout << i << "|"; \
    cout << endl; \
} while (0)
#else
#define debug(x)
#define debugVect(v)
#endif

const int INF = 1e9;
typedef pair<int, int> pii;
const int dy[] = {-1, 1, 0, 0}, dx[] = {0, 0, -1, 1};

int Y, X;
vector<vector<int>> board;

bool inRange(int y, int x) {
    return 0 <= y && y < Y && 0 <= x && x < X;
}

int dijkstra() {
    vector<vector<int>> dist(Y, vector<int>(X, INF));
    vector<vector<bool>> visited(Y, vector<bool>(X, false));

    priority_queue<pair<int, pii>, vector<pair<int, pii>>,
        greater<pair<int, pii>>> pq;

    dist[0][0] = 0;
    pq.push( {0, {0, 0}} );

    while (pq.size()) {
        auto [_, curr] = pq.top(); pq.pop();
        auto [y, x] = curr;
        debug(y); debug(x);

        if (visited[y][x]) continue;
        visited[y][x] = true;

        for (int d = 0; d < 4; d++) {
            int ny = y + dy[d];
            int nx = x + dx[d];
            if (!inRange(ny, nx)) continue;

            if (dist[ny][nx] <= dist[y][x] + board[ny][nx]) continue;
            dist[ny][nx] = dist[y][x] + board[ny][nx];
            pq.push( { dist[ny][nx], {ny, nx}} );
        }
    }
    return dist[Y-1][X-1];
}

int main() {
    cin >> X >> Y;
    board.resize(Y, vector<int>(X));
    for (int y = 0; y < Y; y++)
        for (int x = 0; x < X; x++) {
            char input;
            cin >> input;
            board[y][x] = input - '0';
        }

    cout << dijkstra() << endl;

    return 0;
}