#include <bits/stdc++.h>
#define FASTIO cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(0)
#define endl '\n'
#define UNKNOWN (-1e9 + 1)
using namespace std;

int N, Q;
map<string, int> index_map;
vector<tuple<int, int, int>> equations;
vector<vector<int>> adj; // x + y = z -> adj[x][y] = z

void set_index(string str) {
    if (index_map.count(str)) return;

    int sz = index_map.size();
    index_map[str] = sz;
}

int get_index(string str) {
    if (!index_map.count(str))
        return -1;
    return index_map[str];
}

void input() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        string str_inp; cin >> str_inp;

        // do parse
        int p;
        for (p = 0; str_inp[p] != '='; ++p);
        string eq = str_inp.substr(0, p);
        string str_z = str_inp.substr(p + 1);

        for (p = 0; eq[p] != '+'; ++p);
        string str_x = eq.substr(0, p);
        string str_y = eq.substr(p + 1);

        set_index(str_x);
        set_index(str_y);
        int x = get_index(str_x);
        int y = get_index(str_y);
        int z = stoi(str_z);

        equations.push_back({x, y, z});
    }

    int K = index_map.size();
    adj.resize(K, vector<int>(K, UNKNOWN));

    for (auto &[x, y, z] : equations) {
        adj[x][y] = adj[y][x] = z;
    }
}

void bfs() {
    int K = index_map.size();
    bool updated;

    auto search_internodes = [&](int x, int y, bool &updated) {
        for (int a = 0; a < K; a++) {
            for (int b = 0; b < K; b++) {
                if (adj[x][a] != UNKNOWN && adj[y][b] != UNKNOWN
                    && adj[a][b] != UNKNOWN)
                {
                    int val = adj[x][a] + adj[y][b] - adj[a][b];
                    adj[x][y] = adj[y][x] = val;
                    updated = true;
                    return;
                }
            }
        }
    };

    do {
        for (int x = 0; x < K; x++) {
            updated = false;
            for (int y = 0; y < K; y++) {
                if (adj[x][y] == UNKNOWN) {
                    search_internodes(x, y, updated);
                    if (updated) break;
                }
            }
        }
    } while (updated);
}

void query() {
    int Q; cin >> Q;

    for (int i = 0; i < Q; i++) {
        string str_inp; cin >> str_inp;

        int p;
        for (p = 0; str_inp[p] != '+'; ++p);
        string str_x = str_inp.substr(0, p);
        string str_y = str_inp.substr(p + 1);

        int x = get_index(str_x);
        int y = get_index(str_y);
        if (x == -1 || y == -1) continue;

        if (adj[x][y] != UNKNOWN)
            cout << str_x << "+" << str_y << "=" << adj[x][y] << endl;
    }
}

int main() {
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        index_map.clear();
        equations.clear();
        adj.clear();

        input();
        bfs();
        cout << "Case #" << t << ":" << endl;
        query();
    }

    return 0;
}
