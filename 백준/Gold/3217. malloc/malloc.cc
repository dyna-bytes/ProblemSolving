#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
#include<unordered_set>
#include<unordered_map>
#include <string>
using namespace std;
typedef vector<int> vint;
const int MAX = 1e5;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define debug(x) cout << "[debug] " << #x << " is " << x << endl;

struct Memory {
    int index;
    int size;
    bool isLocked = false;
    Memory* prev = nullptr;
    Memory* next = nullptr;
};

Memory* head;
Memory* tail;
unordered_map<string, Memory*> locked;

void init() {
    head = new Memory();
    tail = new Memory();
    Memory* memory = new Memory();

    head->index = 0;
    head->size = 0;
    head->isLocked = true;

    tail->index = MAX + 1;
    tail->size = 0;
    tail->isLocked = true;

    memory->index = 1;
    memory->size = MAX;

    head->next = memory;
    memory->prev = head;

    memory->next = tail;
    tail->prev = memory;
}

int malloc(string var, int mSize) {
    for (Memory* it = head; it != tail; it = it->next) {
        if (it->size < mSize) continue;
        if (it->isLocked) continue;

        int idx = it->index;
        int size = it->size;

        if (size == mSize) {
            it->isLocked = true;
            locked[var] = it;
            return idx;
        }

        Memory* nextmem = it->next;
        Memory* mem = new Memory();
        
        it->size = mSize;
        mem->size = size - mSize;
        mem->index = idx + mSize;

        it->next = mem;
        mem->prev = it;

        mem->next = nextmem;
        nextmem->prev = mem;

        it->isLocked = true;
        locked[var] = it;
        return idx;
    }

    locked[var] = nullptr;
    return 0;
}

void free(string var) {
    if (locked[var] == nullptr) return;

    Memory* lock = locked[var];
    Memory* prevmem = lock->prev;
    Memory* nextmem = lock->next;

    lock->isLocked = false;
    locked[var] = nullptr;

    if (prevmem->isLocked == false) {
        prevmem->next = nextmem;
        nextmem->prev = prevmem;

        prevmem->size += lock->size;
        lock = prevmem;
    }

    if (nextmem->isLocked == false) {
        lock->next = nextmem->next;
        nextmem->next->prev = lock;

        lock->size += nextmem->size;
    }
}

void print(string var) {
    if (locked[var] == nullptr) cout << 0 << endl;
    else cout << locked[var]->index << endl;
}

int main() {
    FASTIO;
    int N; cin >> N;
    init();

    string s_malloc("malloc");
    string s_free("free");
    string s_print("print");

    for (int i = 0; i < N; i++) {
        string inp; cin >> inp;
        int l_par = 0, r_par = 0;
        while (inp[l_par] != '(') l_par++;
        while (inp[r_par] != ')') r_par++;

        int m = inp.find(s_malloc);
        if (m != string::npos) {
            string var = inp.substr(0, m - 1);
            int size = stoi(inp.substr(l_par + 1, r_par - l_par - 1));
            //debug(var);
            malloc(var, size);
            continue;
        }

        int f = inp.find(s_free);
        if (f != string::npos) {
            string var = inp.substr(l_par + 1, r_par - l_par - 1);
            //debug(var);
            free(var);
            continue;
        }

        int p = inp.find(s_print);
        if (p != string::npos) {
            string var = inp.substr(l_par + 1, r_par - l_par - 1);
            //debug(var);
            print(var);
        }
    }
    return 0;
}