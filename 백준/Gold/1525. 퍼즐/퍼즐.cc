#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define debug(x) cout << "[debug] " << #x << " is " << x << endl;
#define debugV2D(vv) do {\
    cout << "[debug] " << #vv << endl;\
    for (auto v: vv) {\
        for (auto e: v) cout << e << " | ";\
        cout << endl;\
    }\
    cout << endl;\
} while (0)
typedef pair<int, int> pii;
typedef vector<int> vint;
const int dy[] = {-1, 1, 0, 0}, dx[] = {0, 0, -1, 1};
const string ans = "123456780";

bool inRange(int y, int x) { return 0 <= y && y < 3 && 0 <= x && x < 3; }
struct Node {
    string board;
    int y_x; // y = y_x/3, x = y_x%3. y_x: pos in board string
    int f; // f := g + h
    int g; // g := depth
    int set_y_x(int y, int x) {
        return y_x = y * 3 + x;
    }
    pii get_y_x() {
        return { y_x / 3, y_x % 3 };
    }
};
 
// f, g에 대해 오름차순 정렬
struct Compare {
    bool operator()(Node& n1, Node& n2) {
        if (n1.f == n2.f) return n1.g > n2.g;
        return n1.f > n2.f;
    }
};

// def. h = SUM( |board[y][x] != answer[y][x]| )
int heuristic(string& board) {
    int cnt = 0;
    for (int i = 0; i < 9; i++)
        if (board[i] != ans[i]) cnt++;
    return cnt;
}

int bfs(string start, int sy, int sx) {
    priority_queue<Node, vector<Node>, Compare> pq;
    unordered_map<string, int> visited;
    auto SWAP = [&](int y_x, int ny_nx, string board) {
        swap(board[y_x], board[ny_nx]);
        return board;
    };

    Node S;
    S.board = start;
    S.f = heuristic(start);
    S.g = 0;
    S.set_y_x(sy, sx);
    
    pq.push(S);
    visited[start] = true;
    while (!pq.empty()) {
        Node curr = pq.top(); pq.pop();
        auto [y, x] = curr.get_y_x();
        if (curr.board == ans) return curr.g;

        for (int dir = 0; dir < 4; dir++) {
            int ny = y + dy[dir], nx = x + dx[dir];
            if (!inRange(ny, nx)) continue;
            Node next;
            next.board = SWAP(curr.y_x, next.set_y_x(ny, nx), curr.board);
            
            if (visited[next.board]) continue;
            visited[next.board] = true;

            next.g = curr.g + 1;
            next.f = next.g + heuristic(next.board);
            pq.push(next);
        }
    }
    return -1;
}

int main() {
    FASTIO;
    int sy, sx;
    string start;
    for (int y = 0; y < 3; y++)
        for (int x = 0; x < 3; x++) {
            char ch; cin >> ch;
            start += ch;
            if (ch == '0') 
                sy = y, sx = x;
        }
    cout << bfs(start, sy, sx);
    return 0;
}