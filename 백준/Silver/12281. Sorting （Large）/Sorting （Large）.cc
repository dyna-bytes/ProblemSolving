#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define MAXN 1000

int N;
int even_num[MAXN];
int odd_num[MAXN];
int even_pos[MAXN];
int odd_pos[MAXN];
int E, O;
int sorted[MAXN];

void solve() {
    sort(even_num, even_num + E, [](int& a, int& b){
        return a > b;
    });
    for (int i = 0; i < E; i++) 
        sorted[even_pos[i]] = even_num[i];

    sort(odd_num, odd_num + O);
    for (int i = 0; i < O; i++)
        sorted[odd_pos[i]] = odd_num[i];

    for (int i = 0; i < N; i++) cout << sorted[i] << ' ';
    cout << endl;
}

int main() {
    FASTIO;
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        cin >> N;
        E = O = 0;
        for (int i = 0; i < N; i++) {
            int s; cin >> s;
            if ((s & 1) == 0) {
                even_num[E] = s;
                even_pos[E] = i;
                E++;
            } else {
                odd_num[O] = s;
                odd_pos[O] = i;
                O++;
            }
        }
        cout << "Case #" << (t + 1) << ": ";
        solve();
    }
    return 0;
}