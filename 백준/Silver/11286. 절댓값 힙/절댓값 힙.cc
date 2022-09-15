#include <bits/stdc++.h>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define debugVec(v) do { \
    std::cout << "[Debug] ["; \
    for(int i = 0; i < ((v.size())-1); i++) std::cout << v[i] << "|"; \
    std::cout << v[((v.size())-1)] << "]\n"; \
} while(0)
#define debugV2D(v) do { \
    std::cout << "[Debug] [\n"; \
    for(int y = 0; y < (v.size()); y++) { \
        if(v[y].empty()){ std::cout << "  []\n"; continue; } \
        std::cout << "  ["; \
        for(int x = 0; x < ((v[y].size())-1); x++) \
            std::cout << v[y][x] << "|"; \
        std::cout << v[y][(v[y].size())-1] << "]\n"; \
    } \
    std::cout << "]\n"; \
} while(0)
#define endl '\n'
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vint;
typedef vector<pii> vpii;

// ascending ordered absolute value priority queue
class absHeap {
private:
    vpii tree;
public:
    absHeap();
    void push(int);
    void pop();
    int top();
};

absHeap::absHeap() {
    tree.push_back({-1, -1});
}

void absHeap::push(int value) {
    tree.push_back({abs(value), value});
    int idx = tree.size() - 1;
    while (idx > 1) {
        if (tree[idx/2] <= tree[idx]) break;
        swap(tree[idx/2], tree[idx]);
        idx /= 2;
    }
}

void absHeap::pop() {
    if (tree.size() == 1) return;
    tree[1] = tree.back();
    tree.pop_back();

    int idx = 1;
    while (true) {
        int priority = -1;
        if (idx*2 > tree.size() - 1) break;
        else if (idx*2 + 1 > tree.size() - 1) priority = idx*2;
        else if (tree[idx*2] < tree[idx*2 + 1]) priority = idx*2;
        else priority = idx*2 + 1;

        if (tree[idx] <= tree[priority]) break;
        swap(tree[idx], tree[priority]);
        idx = priority;
    }
}

int absHeap::top() {
    if (tree.size() == 1) return 0;
    return tree[1].second;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    absHeap pq;

    int N; cin >> N;
    for (int i = 0; i < N; i++) {
        int op; cin >> op;
        if (op == 0) {
            cout << pq.top() << endl;
            pq.pop();
        } else {
            pq.push(op);
        }
    }
    return 0;
}