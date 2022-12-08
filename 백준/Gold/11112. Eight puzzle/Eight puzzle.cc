#include <stdio.h>
#include <string.h>
#include <string>
#include <queue>
#include <unordered_map>
#include <cassert>
#define SWAP(a, b) { typeof(a) t = a; a = b; b = t; }
const int MAXL = 10;
const int MAXN = 128000;
const int MAX_KEY = 16;
const int MAX_TABLE = 131072;
const int dy[] = {-1, 1, 0, 0}, dx[] = {0, 0, -1, 1};
typedef unsigned long ul;
using namespace std;

struct Node {
    char board[MAXL];
    int y_x; // y = y_x/3, x = y_x%3
    int set_y_x(int y, int x) {
        return y_x = y*3 + x;
    }
    void get_y_x(int& y, int& x) {
        y = y_x/3, x = y_x%3;
    }
};

const char ans[MAXL] = "123456780";
bool inRange(int y, int x) {
    return 0 <= y && y < 3 && 0 <= x && x < 3;
}
void move(int y_x, int ny_nx, char* source, char* dest) {
    strcpy(dest, source);
    SWAP(dest[y_x], dest[ny_nx]);
}

queue<Node> q;
unordered_map<string, int> visited;
void bfs() {
    Node S;
    strcpy(S.board, ans);
    S.set_y_x(2, 2);

    q.push(S);
    visited[S.board] = 1;
    while (!q.empty()) {
        Node curr = q.front(); q.pop();
        int y, x; curr.get_y_x(y, x);
        int depth = visited[curr.board];
        
        for (int d = 0; d < 4; d++) {
            int ny = y + dy[d], nx = x + dx[d];
            if (!inRange(ny, nx)) continue;
            Node next;
            move(curr.y_x, next.set_y_x(ny, nx), curr.board, next.board);

            if (visited[next.board]) continue;
            visited[next.board] = depth + 1;
            q.push(next);
        }
    }
}

int main() {
    bfs();

    int T; scanf("%d", &T);
    while (T--) {
        char inp[MAXL];
        for (int i = 0; i < 9; ) {
            char ch; scanf("%c", &ch);
            if (ch == '\n') continue;
            if (ch == '#') inp[i++] = '0';
            else inp[i++] = ch;
        }
        
        int depth = visited[inp];
        if (strcmp(inp, ans) == 0) printf("0\n");
        else if (depth > 1) printf("%d\n", depth - 1);
        else printf("impossible\n");
    }
    return 0;
}