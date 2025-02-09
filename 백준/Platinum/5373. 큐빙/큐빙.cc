#include <bits/stdc++.h>
#define endl '\n'
#define FASTIO cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define debug_Z_AXIS(v, z) do { \
    std::cout << "[Debug] [\n"; \
    for(int y = 0; y < SPACE_LEN; y++) { \
        std::cout << "  ["; \
        for(int x = 0; x < SPACE_LEN; x++) \
            std::cout << v[z][y][x].symbol << "|"; \
        std::cout << "]\n"; \
    } \
    std::cout << "]\n"; \
} while(0)
#define debug_Y_AXIS(v, y) do { \
    std::cout << "[Debug] [\n"; \
    for(int z = 0; z < SPACE_LEN; z++) { \
        std::cout << "  ["; \
        for(int x = 0; x < SPACE_LEN; x++) \
            std::cout << v[z][y][x].symbol << "|"; \
        std::cout << "]\n"; \
    } \
    std::cout << "]\n"; \
} while(0)

typedef struct {
    char symbol;
    int z, y, x;
} element;

const int SPACE_LEN = 5;
const int TOP = SPACE_LEN - 1;
element gSpace[SPACE_LEN][SPACE_LEN][SPACE_LEN];
enum AXIS {
    Z_AXIS,
    Y_AXIS,
    X_AXIS
};

void __rotate(pair<int, int>& src, pair<int, int>& dest, pair<int, int>& base, bool anticlockwise) {
    int dir = (anticlockwise) ? 1 : -1;
    auto& [y_dest, x_dest] = dest;
    auto& [y, x] = src;
    auto& [y_0, x_0] = base;

    y_dest = dir * -(x - x_0) + y_0;
    x_dest = dir * (y - y_0) + x_0;
}

void rotate_plane(int x0, enum AXIS axis, bool anticlockwise) {
    element dest_elems[SPACE_LEN * SPACE_LEN];
    int dest_idx = 0;
    pair<int, int> base = { SPACE_LEN/2, SPACE_LEN/2 };

    int z, y, x;
    for (int x1 = 0; x1 < SPACE_LEN; x1++)
        for (int x2 = 0; x2 < SPACE_LEN; x2++) {
            if (axis == Z_AXIS)
                z = x0, y = x1, x = x2;
            else if (axis == Y_AXIS)
                z = x1, y = x0, x = x2;
            else if (axis == X_AXIS)
                z = x1, y = x2, x = x0;

            if (!gSpace[z][y][x].symbol) continue;

            pair<int, int> dest;
            pair<int, int> src;
            if (axis == Z_AXIS)
                src = { gSpace[z][y][x].y, gSpace[z][y][x].x };
            else if (axis == Y_AXIS)
                src = { gSpace[z][y][x].z, gSpace[z][y][x].x };
            else if (axis == X_AXIS)
                src = { gSpace[z][y][x].z, gSpace[z][y][x].y };

            __rotate(src, dest, base, anticlockwise);
            dest_elems[dest_idx] = gSpace[z][y][x];

            if (axis == Z_AXIS)
                dest_elems[dest_idx].y = dest.first,
                dest_elems[dest_idx].x = dest.second;
            else if (axis == Y_AXIS)
                dest_elems[dest_idx].z = dest.first,
                dest_elems[dest_idx].x = dest.second;
            else if (axis == X_AXIS)
                dest_elems[dest_idx].z = dest.first,
                dest_elems[dest_idx].y = dest.second;
            dest_idx++;
        }

    for (int i = 0; i < dest_idx; i++) {
        auto [z, y, x] = tuple<int, int, int>{
            dest_elems[i].z, dest_elems[i].y, dest_elems[i].x};
        gSpace[z][y][x] = dest_elems[i];
    }
}

void cmd_interpret(pair<char, char> cmd) {
    auto [target, anticlockwise] = cmd;
    int acw = (anticlockwise == '-');

    if (target == 'U') {
        rotate_plane(TOP, Z_AXIS, acw);
        rotate_plane(TOP-1, Z_AXIS, acw);
    } else if (target == 'D') {
        rotate_plane(0, Z_AXIS, !acw);
        rotate_plane(1, Z_AXIS, !acw);
    } else if (target == 'F') {
        rotate_plane(TOP, Y_AXIS, !acw);
        rotate_plane(TOP-1, Y_AXIS, !acw);
    } else if (target == 'B') {
        rotate_plane(0, Y_AXIS, acw);
        rotate_plane(1, Y_AXIS, acw);
    } else if (target == 'R') {
        rotate_plane(TOP, X_AXIS, acw);
        rotate_plane(TOP-1, X_AXIS, acw);
    } else if (target == 'L') {
        rotate_plane(0, X_AXIS, !acw);
        rotate_plane(1, X_AXIS, !acw);
    }
}

void print_z_plane() {
    for (int y = 1; y < TOP; y++) {
        for (int x = 1; x < TOP; x++)
            cout << gSpace[TOP][y][x].symbol;
        cout << endl;
    }
}

void init() {
    auto fill = [&](int x0, char symbol, enum AXIS axis) {
        int z, y, x;

        for (int x1 = 1; x1 < TOP; x1++)
            for (int x2 = 1; x2 < TOP; x2++) {
                if (axis == Z_AXIS)
                    z = x0, y = x1, x = x2;
                else if (axis == Y_AXIS)
                    z = x1, y = x0, x = x2;
                else if (axis == X_AXIS)
                    z = x1, y = x2, x = x0;

                gSpace[z][y][x] = {.symbol=symbol, .z=z, .y=y, .x=x};
            }
    };

    // 윗 면 흰색 (z = top)
    fill(TOP, 'w', Z_AXIS);

    // 아랫 면 노란색 (z = 0)
    fill(0, 'y', Z_AXIS);

    // 앞 면 빨간 색 (y = top)
    fill(TOP, 'r', Y_AXIS);

    // 뒷 면 오렌지 색 (y = 0)
    fill(0, 'o', Y_AXIS);

    // 오른쪽 면 파란색 (x = top)
    fill(TOP, 'b', X_AXIS);

    // 왼쪽 면 초록색 (x = 0)
    fill(0, 'g', X_AXIS);
}

int main() {
    FASTIO;
    int T; cin >> T;
    while (T) {
        int N; cin >> N;
        init();
        for (int i = 0; i < N; i++) {
            string token;
            cin >> token;
            char target = token[0], sign = token[1];
            cmd_interpret({target, sign});
        }
        print_z_plane();
        T--;
    }

    return 0;
}