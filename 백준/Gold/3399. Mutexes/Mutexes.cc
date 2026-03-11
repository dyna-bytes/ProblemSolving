#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define FASTIO() ios_base::sync_with_stdio(false), cin.tie(NULL);
#define debug(x) cout << #x << " is " << x << endl;
#define debugVect(v) do { \
    cout << #v << " is |"; \
    for (auto e: v) cout << e << "|"; \
    cout << endl; \
} while (0)

enum instr_opcode_t {
	OP_LOCK,
	OP_UNLOCK
};

struct instr {
	instr_opcode_t opcode;
	int operand;
};

int M;
vector<vector<instr>> tasks;
set<vector<int>> visited;

bool all_done(vector<int>& pc_state) {
    for (int tid = 0; tid < M; ++tid)
        if (pc_state[tid] < tasks[tid].size()) return false;
    return true;
}

vector<int> get_mutex_owners(const vector<int>& pc_state) {
    vector<int> owners(26, -1);

    for (int tid = 0; tid < M; ++tid) {
        // 각 스레드의 0번 명령부터 현재 PC "직전"까지 실행하며 소유권 갱신
        for (int pc = 0; pc < pc_state[tid]; ++pc) {
            auto [opcode, operand] = tasks[tid][pc];
            if (opcode == OP_LOCK) {
                owners[operand] = tid;
            } else if (opcode == OP_UNLOCK) {
                owners[operand] = -1;
            }
        }
    }
    return owners;
}

bool dfs(vector<int>& pc_state) {
    if (visited.count(pc_state)) return false;
    visited.insert(pc_state);

    if (all_done(pc_state)) return false;

    vector<int> mutex_owners = get_mutex_owners(pc_state);
    bool deadlock = true;

    for (int tid = 0; tid < M; ++tid) {
        if (pc_state[tid] == tasks[tid].size()) continue;

        auto [opcode, operand] = tasks[tid][pc_state[tid]];
        if (opcode == OP_UNLOCK || (opcode == OP_LOCK && mutex_owners[operand] == -1)) {
            deadlock = false;
            pc_state[tid]++;

            if (dfs(pc_state)) return true;
            pc_state[tid]--;
        }
    }

    if (deadlock) {
        cout << "1" << endl;
        for (int tid = 0; tid < M; ++tid) {
            if (pc_state[tid] == tasks[tid].size()) {
                cout << -1 << " ";
            } else {
                cout << pc_state[tid] << " ";
            }
        }
        cout << endl;
        return true;
    }
    return false;
}

void solve() {
    vector<int> state(M, 0);
    if (!dfs(state))
        cout << "0" << endl;
}
int main() {
    FASTIO();
    cin >> M;

    tasks.resize(M);
    for (int i = 0; i < M; ++i) {
        int N; cin >> N;
        tasks[i].resize(N);

        for (int j = 0; j < N; ++j) {
            string inp; char rsc;
            cin >> inp >> rsc;

            if (inp == "LOCK")
                tasks[i][j] = { OP_LOCK, rsc - 'A' };
            else if (inp == "UNLOCK")
                tasks[i][j] = { OP_UNLOCK, rsc - 'A' };
        }
    }

    solve();
    return 0;
}