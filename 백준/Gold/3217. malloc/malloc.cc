#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'

// #define DBG
#ifdef DBG
#define debug(x) cout << #x << " is " << x << endl;
#else
#define debug(x)
#endif

#ifndef bit_ceil
unsigned int bit_ceil(unsigned int n) {
    if (n <= 1) return 1;
    return 1 << (32 - __builtin_clz(n - 1));
}
#endif
#ifndef bit_width
int bit_width(unsigned int n) {
    if (n == 0) return -1;
    return (sizeof(unsigned int) * 8 - 1) - __builtin_clz(n);
}
#endif

const int MAX_MEM = 1e5;
const int HASH_SIZE = 26*26*26*26; 

struct Block {
    int size;
    bool is_alloc;
    int prev_addr;
    struct Block* prev = nullptr;
    struct Block* next = nullptr;
} pool[MAX_MEM + 5];

int Hash[HASH_SIZE];
int get_hash(const string& var) {
    int hash = 0;
    for (int i = 0; i < 4; i++)
        hash = hash * 26 + (var[i] - 'a');
    return hash;
}

Block* free_lists[32];

void remove_from_freelist(Block *curr) {
    int list_idx = bit_width(curr->size);

    if (curr->prev) curr->prev->next = curr->next;
    else free_lists[list_idx] = curr->next;

    if (curr->next) curr->next->prev = curr->prev;

    curr->prev = curr->next = nullptr;
}

void insert_into_freelist(Block *curr) {
    int list_idx = bit_width(curr->size);

    curr->next = free_lists[list_idx];
    curr->prev = nullptr;

    if (free_lists[list_idx]) free_lists[list_idx]->prev = curr;
    free_lists[list_idx] = curr;
}

Block* coalesce(int curr_addr) {
    Block* curr = &pool[curr_addr];

    int next_addr = curr_addr + curr->size;
    bool next_is_free = (next_addr <= MAX_MEM && !pool[next_addr].is_alloc);

    int prev_addr = curr->prev_addr;
    bool prev_is_free = (prev_addr > 0 && !pool[prev_addr].is_alloc);

    // Case 2: 뒤쪽(Next)만 Free
    if (!prev_is_free && next_is_free) {
        remove_from_freelist(&pool[next_addr]);
        curr->size += pool[next_addr].size;

        int next_next_addr = curr_addr + curr->size;
        if (next_next_addr <= MAX_MEM + 1) pool[next_next_addr].prev_addr = curr_addr;
    } 
    // Case 3: 앞쪽(Prev)만 Free
    else if (prev_is_free && !next_is_free) {
        Block* prev = &pool[prev_addr];
        remove_from_freelist(prev);

        prev->size += curr->size;
        curr = prev;
        curr_addr = prev_addr;

        int next_next_addr = curr_addr + curr->size;
        // [FIX] Sentinel Update
        if (next_next_addr <= MAX_MEM + 1) pool[next_next_addr].prev_addr = curr_addr;
    } 
    // Case 4: 양쪽 다 Free
    else if (prev_is_free && next_is_free) {
        Block* prev = &pool[prev_addr];
        Block* next = &pool[next_addr];
        remove_from_freelist(prev);
        remove_from_freelist(next);

        prev->size += curr->size + next->size;
        curr = prev;
        curr_addr = prev_addr;

        int next_next_addr = curr_addr + curr->size;
        if (next_next_addr <= MAX_MEM + 1) pool[next_next_addr].prev_addr = curr_addr;
    }

    insert_into_freelist(curr);
    return curr;
}

int find_fit(int req_size) {
    int list_idx = bit_width(req_size);

    Block* best = nullptr;
    int min_addr = INT_MAX;

    for (int i = list_idx; i < 32; i++) {
        Block* curr = free_lists[i];
        while (curr) {
            if (curr->size >= req_size) {
                int curr_addr = (int)(curr - pool);
                if (curr_addr < min_addr) {
                    min_addr = curr_addr;
                    best = curr;
                }
            }
            curr = curr->next;
        }
    }
    
    if (!best) return 0;
    return (int)(best - pool);
}

void place(int addr, int req_size) {
    Block* curr = &pool[addr];
    int total_size = curr->size;
    int remain_size = total_size - req_size;

    remove_from_freelist(curr);

    if (remain_size > 0) {
        curr->size = req_size;
        curr->is_alloc = true;

        int next_addr = addr + req_size;
        pool[next_addr].size = remain_size;
        pool[next_addr].is_alloc = false;
        pool[next_addr].prev_addr = addr;

        int next_next_addr = next_addr + remain_size;
        
        if (next_next_addr <= MAX_MEM + 1) pool[next_next_addr].prev_addr = next_addr;

        insert_into_freelist(&pool[next_addr]);
    } else {
        curr->is_alloc = true;
    }
}

void init() {
    for (int i = 0; i < 32; i++) free_lists[i] = nullptr;
    
    pool[1].size = MAX_MEM;
    pool[1].is_alloc = false;
    pool[1].prev_addr = 0;

    pool[1 + MAX_MEM].prev_addr = 1; 
    pool[1 + MAX_MEM].is_alloc = true; 
    pool[1 + MAX_MEM].size = 0;

    insert_into_freelist(&pool[1]);
}

int user_malloc(const string& var, int req_size) {
    int key = get_hash(var);

    int addr;
    if ((addr = find_fit(req_size))) {
        place(addr, req_size);
        Hash[key] = addr;
        return addr;
    }

    Hash[key] = 0; 
    return 0;
};

void user_free(const string& var) {
    int key = get_hash(var);
    if (!Hash[key]) return; 

    int addr = Hash[key];
    
    pool[addr].is_alloc = false; 
    Hash[key] = 0; 
    
    coalesce(addr); 
}

void user_print(const string& var) {
    int key = get_hash(var);
    cout << Hash[key] << endl;
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

        string var;
        int size;
        int s_idx;

        if ((s_idx = inp.find(s_malloc)) != string::npos) {
            var = inp.substr(0, s_idx - 1); // "abcd=malloc" -> abcd
            size = stoi(inp.substr(l_par + 1, r_par - l_par - 1));
            user_malloc(var, size);
        } else if ((s_idx = inp.find(s_free)) != string::npos) {
            var = inp.substr(l_par + 1, r_par - l_par - 1);
            user_free(var);
        } else if ((s_idx = inp.find(s_print)) != string::npos) {
            var = inp.substr(l_par + 1, r_par - l_par - 1);
            user_print(var);
        }
    }
}

int main() {
    FASTIO;
    init();
    solve();
    return 0;
}