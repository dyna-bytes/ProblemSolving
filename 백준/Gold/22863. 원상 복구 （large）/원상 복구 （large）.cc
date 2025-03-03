#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define FASTIO cin.tie(0)->sync_with_stdio(0)

typedef unsigned long u64;
#define MAX_N int(1e6 + 1)
#define MAX_K u64(1e15 + 1)
#define MAX_LOG_K (50)

u64 N, K;
int S[MAX_N];
int next_card[MAX_LOG_K][MAX_N];
int S2P[MAX_N];

void unshuffle() {
    for (int i = 0; i < MAX_LOG_K-1; i++)
        for (int j = 1; j <= N; j++)
            next_card[i+1][j] = next_card[i][ next_card[i][j] ];

    for (int i = 1; i <= N; i++) {
        int card_idx = i;
        for (int bit = 0; bit < MAX_LOG_K; bit++)
            if (((u64)1 << bit) & K){
                // cout << card_idx << endl;
                card_idx = next_card[bit][card_idx];
            }

        // cout << "card_idx: " << card_idx << " S[card_idx]: " << S[card_idx] << endl;
        // cout << "----" << endl;
        S2P[card_idx] = i;
    }

    for (int i = 1; i <= N; i++)
        cout << S[S2P[i]] << " ";
}

int main() {
    FASTIO;
    cin >> N >> K;
    for (int i = 1; i <= N; i++) cin >> S[i];
    for (int i = 1; i <= N; i++) {
        int card_idx; cin >> card_idx;
        next_card[0][i] = card_idx;
    }
    unshuffle();
    return 0;
}