#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vint;

int solve(int na, int nb, vint& va, vint& vb) {
    set<int> A;

    for (int a: va) 
        A.insert(a);

    int intersect = 0;
    for (int b: vb) {
        auto it = A.find(b);
        if (it != A.end()) intersect++;
    }

    return na + nb - 2*intersect;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int na, nb;
    cin >> na >> nb;
    vint va(na), vb(nb);
    for (int i = 0; i < na; i++) cin >> va[i];
    for (int i = 0; i < nb; i++) cin >> vb[i];

    cout << solve(na, nb, va, vb);
    return 0;
}