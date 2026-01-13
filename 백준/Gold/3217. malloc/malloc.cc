#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
// #define DBG
#ifdef DBG
#define debug(x) cout << #x << " is " << x << endl;
#else
#define debug(x)
#endif

const int MAX_SIZE = 1e5;

struct Memory {
    int addr;
    int size;
    bool isAlloced = false;
    struct Memory *prev = nullptr;
    struct Memory *next = nullptr;
} pool[MAX_SIZE + 5];

int sp = 0;
struct Memory *pool_alloc() {
    return &pool[sp++];
}

struct Memory *head;
struct Memory *tail;
unordered_map<string, Memory*> alloced;

void init() {
    head = pool_alloc();
    tail = pool_alloc();
    Memory *memory = pool_alloc();

    head->addr = 0;
    head->size = 0;
    head->isAlloced = true;

    tail->addr = MAX_SIZE + 1;
    tail->size = 0;
    tail->isAlloced = true;

    memory->addr = 1;
    memory->size = MAX_SIZE;

    head->next = memory;
    memory->prev = head;

    memory->next = tail;
    tail->prev = memory;
}

int user_malloc(const string& var, int mSize) {
    for (Memory *it = head; it != tail; it = it->next) {
        if (it->size < mSize) continue;
        if (it->isAlloced) continue;

        int addr = it->addr;
        int size = it->size;

        if (size == mSize) {
            it->isAlloced = true;
            alloced[var] = it;
            return addr;
        }

        Memory *next = it->next;
        Memory *remain = pool_alloc();

        it->size = mSize;
        remain->size = size - mSize;
        remain->addr = addr + mSize;

        it->next = remain;
        remain->prev = it;

        remain->next = next;
        next->prev = remain;

        it->isAlloced = true;
        alloced[var] = it;
        return addr;
    }

    alloced[var] = nullptr;
    return 0;
};

void user_free(const string& var) {
    if (!alloced[var]) return;

    Memory *mem = alloced[var];
    Memory *prev = mem->prev;
    Memory *next = mem->next;

    alloced[var] = nullptr;
    mem->isAlloced = false;
    if (!prev->isAlloced) {
        prev->next = next;
        next->prev = prev;

        prev->size += mem->size;
        mem = prev;
    }

    if (!next->isAlloced) {
        mem->next = next->next;
        next->next->prev = mem;

        mem->size += next->size;
    }
}

void user_print(const string& var) {
    if (!alloced[var]) cout << 0 << endl;
    else cout << alloced[var]->addr << endl;
}

void solve() {
    int n;
    cin >> n;

    const string s_malloc = "malloc";
    const string s_free = "free";
    const string s_print = "print";
    for (int i = 0; i < n; i++) {
        string inp; cin >> inp;
        int l_par = 0, r_par = 0;
        while (inp[l_par] != '(') l_par++;
        while (inp[r_par] != ')') r_par++;

        int s_idx;
        string var;
        int size;
        if ((s_idx = inp.find(s_malloc)) != string::npos) {
            var = inp.substr(0, s_idx - 1);
            size = stoi(inp.substr(l_par + 1, r_par - l_par - 1));
            debug(var);
            debug(size);
            user_malloc(var, size);
        } else if ((s_idx = inp.find(s_free)) != string::npos) {
            var = inp.substr(l_par + 1, r_par - l_par - 1);
            debug(var);
            user_free(var);
        } else if ((s_idx = inp.find(s_print)) != string::npos) {
            var = inp.substr(l_par + 1, r_par - l_par - 1);
            debug(var);
            user_print(var);
        } else
            cout << "Error inp " << inp << endl;
    }
}
int main() {
    FASTIO;
    init();
    solve();
    return 0;
}