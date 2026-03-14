#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define FASTIO() ios_base::sync_with_stdio(false), cin.tie(NULL);
#define DBG 0
#if DBG
#define debug(x) cout << "[" << __func__ << "](" << __LINE__ << ") " << #x << " is " << x << endl;
#define debugVect(v) do { \
    cout << #v << " is |"; \
    for (auto e: v) cout << e << "|"; \
    cout << endl; \
} while (0)
#else
#define debug(x)
#define debugVect(v)
#endif

#define EOK				(0)
#define ESYSCALL_EBUSY	(-1)
#define ESYSCALL_PANIC	(-2)
#define ESYSCALL_ACCESS (-3)

const int MAXM = 50000;

enum instr_opcode_t {
	OP_LOCK,
	OP_UNLOCK,
    OP_ACCESS,
    OP_JUMP,
};

struct instr {
    instr_opcode_t opcode;
    int operand;
};

vector<int> topo_sort(const vector<vector<int>>& adj) {
    vector<int> ret;
    vector<int> indeg(adj.size());

    for (const vector<int>& node: adj)
        for (int x: node)
            indeg[x]++;

    queue<int> q;
    for (int i = 0; i < indeg.size(); i++)
        if (indeg[i] == 0) q.push(i);

    while (q.size()) {
        int curr = q.front(); q.pop();
        ret.push_back(curr);
        for (int next: adj[curr])
            if (--indeg[next] == 0)
                q.push(next);
    }
    return ret;
}

int lookup(map<string, int>& mp, const string& s) {
    if (mp.count(s)) return mp[s];
    return mp[s] = mp.size();
};

vector<bitset<MAXM>> need_unlocked_all;
vector<bitset<MAXM>> need_locked_all;
vector<bitset<MAXM>> result_unlocked_all;
vector<bitset<MAXM>> result_locked_all;
vector<bool> has_error;

int solve(int N, map<string, int>& fns,
        map<string, int>& muts,
        map<int, vector<instr>>& funcs)
{
    int main_id = lookup(fns, "main");
    vector<vector<int>> adj(N);

    for (int i = 0; i < N; i++)
        for (auto& [opcode, operand]: funcs[i])
            if (opcode == OP_JUMP)
                adj[i].push_back(operand);

    vector<int> order = topo_sort(adj);
    reverse(order.begin(), order.end());

    need_unlocked_all.resize(N);
    need_locked_all.resize(N);
    result_unlocked_all.resize(N);
    result_locked_all.resize(N);
    has_error.resize(N, false);

    for (int fn_id: order) {
        bitset<MAXM> need_unlocked, need_locked;
        bitset<MAXM> locked, touched;
        bool err = false;

        if (fn_id == main_id) touched.flip();

        for (auto& [opcode, x]: funcs[fn_id]) {
            if (opcode == OP_LOCK) {
                if (!touched[x]) {
                    touched[x] = true;
                    need_unlocked[x] = true;
                    locked[x] = true;
                } else if (locked[x]) {
                    err = true;
                } else {
                    locked[x] = true;
                }
            }
            else if (opcode == OP_UNLOCK) {
                if (!touched[x]) {
                    touched[x] = true;
                    need_locked[x] = true;
                    locked[x] = false;
                } else if (!locked[x]) {
                    err = true;
                } else {
                    locked[x] = false;
                }
            }
            else if (opcode == OP_ACCESS) {
                if (!touched[x]) {
                    touched[x] = true;
                    need_locked[x] = true;
                    locked[x] = true;
                } else if (!locked[x]) {
                    err = true;
                }
            }
            else if (opcode == OP_JUMP) {
                bitset<MAXM> child_need_unlocked = need_unlocked_all[x];
                bitset<MAXM> child_need_locked = need_locked_all[x];
                bitset<MAXM> child_result_unlocked = result_unlocked_all[x];
                bitset<MAXM> child_result_locked = result_locked_all[x];

                if (has_error[x] ||
                (child_need_unlocked & locked).any() ||
                (child_need_locked & ~locked & touched).any()) {
                    err = true;
                } else {
                    need_unlocked |= ~touched & child_need_unlocked;
                    need_locked |= ~touched & child_need_locked;

                    touched |= child_result_unlocked;
                    touched |= child_result_locked;

                    locked |= child_result_locked;
                    locked &= ~child_result_unlocked;
                }
            }
        }

        need_unlocked_all[fn_id] = need_unlocked;
        need_locked_all[fn_id] = need_locked;
        result_unlocked_all[fn_id] = ~locked & touched;
        result_locked_all[fn_id] = locked;
        has_error[fn_id] = err;
    }

    if (has_error[main_id])
        return -1;
	return 0;
}

int simulate(int fn_id, bitset<MAXM> locked, map<int, vector<instr>>& funcs) {
    for (auto& [opcode, x]: funcs[fn_id]) {
        if (opcode == OP_LOCK) {
            if (locked[x])
                return ESYSCALL_EBUSY;
            locked[x] = true;
        }
        else if (opcode == OP_UNLOCK) {
            if (!locked[x])
                return ESYSCALL_PANIC;

            locked[x] = false;
        }
        else if (opcode == OP_ACCESS) {
            if (!locked[x])
                return ESYSCALL_ACCESS;
        }
        else if (opcode == OP_JUMP) {
            bitset<MAXM> child_need_unlocked = need_unlocked_all[x];
            bitset<MAXM> child_need_locked = need_locked_all[x];
            bitset<MAXM> child_result_unlocked = result_unlocked_all[x];
            bitset<MAXM> child_result_locked = result_locked_all[x];

            if (has_error[x] ||
            (child_need_unlocked & locked).any() ||
            (child_need_locked & ~locked).any())
                return simulate(x, locked, funcs);
            else {
                locked |= child_result_locked;
                locked &= ~child_result_unlocked;
            }
        }
    }

    return EOK;
}

int main() {
    FASTIO();
    int N; cin >> N;
    map<string, int> fns, muts;
    map<int, vector<instr>> funcs;

    for (int i = 0; i < N; i++) {
        int M; string name;
        cin >> M >> name;

        int fn_id = lookup(fns, name);
        vector<instr> stack_frame(M);

        for (int j = 0; j < M; j++) {
            string op, rsc;
            cin >> op >> rsc;

            if (op == "call") {
                stack_frame[j] = { OP_JUMP, lookup(fns, rsc) };
            } else {
                int rsc_id = lookup(muts, rsc);
                if (op == "acquire") stack_frame[j] = { OP_LOCK, rsc_id };
                else if (op == "release") stack_frame[j] = { OP_UNLOCK, rsc_id };
                else if (op == "access") stack_frame[j] = { OP_ACCESS, rsc_id };
            }
        }
        funcs[fn_id] = stack_frame;
    }

    int ret = solve(N, fns, muts, funcs);
    if (ret == 0)
        cout << "a-ok" << endl;
    else {
        ret = simulate(lookup(fns, "main"), bitset<MAXM>(), funcs);
        if (ret == ESYSCALL_EBUSY) cout << "deadlock" << endl;
        else if (ret == ESYSCALL_PANIC) cout << "error" << endl;
        else if (ret == ESYSCALL_ACCESS) cout << "corruption" << endl;
    }
    return 0;
}