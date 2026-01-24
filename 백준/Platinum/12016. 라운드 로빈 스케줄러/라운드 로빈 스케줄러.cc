#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define DBG
#ifdef DBG
#define debug(x) cout << "[" << __func__ << "](" << __LINE__ << ") " << #x << " is " << x << endl;
#define debugVect(v) do { \
    cout << "[" << __func__ << "](" << __LINE__ << ") " << #v << " is |\t"; \
    for (auto e: v) cout << e << "|\t" ; \
    cout << endl; \
} while (0)
#define debugVect2d(vv) do { \
    cout << "[" << __func__ << "](" << __LINE__ << ") " << #vv << " is " << endl; \
    for (auto v: vv) debugVect(v); \
} while (0)
#else
#define debug(x)
#define debugVect(v)
#define debugVect2d(vv)
#endif
typedef long long ll;
typedef pair<ll, ll> pll;

class SegTree {
    int size;
    vector<ll> tree;
    void insert(int node, int s, int e, int idx, int val) {
        if (idx < s || e <= idx) return;
        tree[node] += val;

        if (s + 1 == e) return;
        int m = (s + e)/2;
        insert(node*2, s, m, idx, val);
        insert(node*2 + 1, m, e, idx, val);
    }
    void update(int node, int s, int e, int idx, int val) {
        if (idx < s || e <= idx) return;
        if (s + 1 == e) {
            tree[node] = val;
            return;
        }

        int m = (s + e)/2;
        update(node*2, s, m, idx, val);
        update(node*2 + 1, m, e, idx, val);

        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }
    ll sum(int node, int x, int y, int s, int e) {
        if (y <= s || e <= x) return 0;
        if (s <= x && y <= e) return tree[node];

        int m = (x + y)/2;
        return sum(node*2, x, m, s, e) +
            sum(node*2 + 1, m, y, s, e);
    }
public:
    SegTree(int n) {
        size = 1;
        while (size < n) size *= 2;
        size *= 2;
        tree.resize(size + 1);
    }
    ll set_node(int idx, int val) {
        return tree[size/2 + idx] = val;
    }
    ll get_node(int idx) {
        return tree[size/2 + idx];
    }

    void construct() {
        for (int i = size/2 - 1; i > 0; i--)
            tree[i] = tree[i*2] + tree[i*2 + 1];
    }

    void insert(int idx, int val) {
        insert(1, 0, size/2, idx, val);
    }

    void update(int idx, int val) {
        update(1, 0, size/2, idx, val);
    }

    // sum in range of [s, e)
    ll sum(int s, int e) {
        return sum(1, 0, size/2, s, e);
    }
};

void solve(int n, vector<ll>& jobs) {
    vector<pll> tasks(n);
    for (int i = 0; i < n; i++)
        tasks[i] = { jobs[i], i };

    sort(tasks.begin(), tasks.end());

    SegTree segTree(n + 1);
    for (int i = 0; i < n; i++)
        segTree.set_node(i, 1);
    segTree.construct();

    ll total_time = 0;
    ll prev_T = 0;
    ll remain_tasks = n;

    vector<ll> ans(n, 0);
    for (int i = 0; i < n; i++) {
        int j = i;
        while (j < n && tasks[i].first == tasks[j].first)
            j++;

        ll curr_T = tasks[i].first;

        ll full_cycles = curr_T - prev_T - 1;
        total_time += full_cycles * remain_tasks;

        for (int k = i; k < j; k++) {
            int task_idx = tasks[k].second;
            ans[task_idx] = total_time + segTree.sum(0, task_idx + 1);
        }

        total_time += remain_tasks;

        for (int k = i; k < j; k++) {
            int task_idx = tasks[k].second;
            segTree.update(task_idx, 0);
            remain_tasks--;
        }

        prev_T = curr_T;
        i = j - 1;
    }

    for (ll a: ans)
        cout << a << endl;
}

int main() {
    int n;
    cin >> n;

    vector<ll> jobs(n);
    for (ll& job: jobs) cin >> job;

    solve(n, jobs);

    return 0;
}