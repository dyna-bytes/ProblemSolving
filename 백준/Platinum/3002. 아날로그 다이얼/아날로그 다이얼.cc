#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
typedef long long ll;
const int MAXN = 1 << 21;

int N, M, K;
string str;

ll tree[MAXN][10];
ll lazy[MAXN];
struct LazyProp {
    void prop(int node, int ns, int ne) {
        int temp[10] = { 0,0,0,0,0,0,0,0,0,0 };

        if (lazy[node]) {
            for (int i = 0; i < 10; i++) temp[(i + lazy[node]) % 10] = tree[node][i];
            for (int i = 0; i < 10; i++) tree[node][i] = temp[i];

            if (ns + 1 < ne) {
                lazy[node*2] += lazy[node];
                lazy[node*2 + 1] += lazy[node];
            }
        }

        lazy[node] = 0;
    }

    void init(int node, int ns, int ne) {
        if (ns + 1 == ne) {
            tree[node][str[ns] - '0'] = 1;
            return;
        }

        int mid = (ns + ne)/2;
        init(node*2, ns, mid);
        init(node*2 + 1, mid, ne);
        for (int i = 0; i < 10; i++) tree[node][i] = tree[node*2][i] + tree[node*2+1][i];
    }

    void add(int qs, int qe, ll val){ add(qs, qe, val, 1, 0, N); }
    void add(int qs, int qe, ll val, int node, int ns, int ne) {
        prop(node, ns, ne);

        if (qe <= ns || ne <= qs) return;
        if (qs <= ns && ne <= qe) {
            lazy[node] += val;
            prop(node, ns, ne);
            return;
        }

        int mid = (ns + ne)/2;
        add(qs, qe, val, node*2, ns, mid);
        add(qs, qe, val, node*2 + 1, mid, ne);
        for (int i = 0; i < 10; i++) tree[node][i] = tree[node*2][i] + tree[node*2 + 1][i];
    }

    ll sum(int qs, int qe) { return sum(qs, qe, 1, 0, N); }
    ll sum(int qs, int qe, int node, int ns, int ne) {
        prop(node, ns, ne);

        ll ret = 0;
        if (qe <= ns || ne <= qs) return 0;
        if (qs <= ns && ne <= qe) {
            for (int i = 0; i < 10; i++) ret += i * tree[node][i];
            return ret;
        }

        int mid = (ns + ne)/2;
        return sum(qs, qe, node*2, ns, mid) + sum(qs, qe, node*2 + 1, mid, ne);
    }
};

int main() {
    FASTIO;
    cin >> N >> M;
    cin >> str;
    LazyProp ST;
    ST.init(1, 0, N);

    while (M--) {
        int A, B; cin >> A >> B;
        cout << ST.sum(A-1, B) << endl;
        ST.add(A-1, B, 1);
    }

    return 0;
}