#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0)
#define endl '\n'
#define debug(x) cout << "[debug] " << #x << " is " << x << endl
typedef vector<int> vint;

const vint truthTable = {
    0b1111110, // 0
    0b0110000, // 1
    0b1101101, // 2
    0b1111001, // 3
    0b0110011, // 4
    0b1011011, // 5
    0b1011111, // 6
    0b1110000, // 7 
    0b1111111, // 8
    0b1111011  // 9
};

int N;
vint display;
int filter;
int neg_filter;
void input() {
    cin >> N;
    display = {}; display.resize(N);
    filter = 0;
    neg_filter = 0x7F;

    for (int i = 0; i < N; i++) {
        int binary = 0;
        string str; cin >> str;
        for (int i = 0; i < 7; i++) {
            binary <<= 1;
            binary += (str[i] == '1');
        }
        display[i] = binary;
        filter |= binary;
    }
}

inline void printbits(int bits) {
    for (int i = 6; i >= 0; --i)
        cout << ((bits >> i) & 1);
    cout << endl;
}

void solve() {
    int ans = -1;
    int n = 0;
    for (int i = 9; i >= 0; i--) {
        n = 0;
        if ((truthTable[i] & filter) == display[n++]) {
            bool pass = true;
            int j = (i + 9) % 10;
            for (int cnt = 1; cnt < N; (j += 9) %= 10, cnt++) 
                if ((truthTable[j] & filter) != display[n++]) pass = false;
            
            if (pass) {
                if (ans != -1) {
                    cout << "ERROR!" << endl;
                    return;
                }
                
                ans = j;
            }
        }
    }

    if (ans == -1) {
        cout << "ERROR!" << endl;
        return;
    }

    // 고장난 것인지 안켜진 것인지 불분명한 애들 검출
    // -> 진리표에서도 0이고 디스플레이에서도 0인 비트들을 neg_filter에 기록
    n = 0;
    for (int i = (ans + N) % 10; i != ans; i = (i + 9) % 10) 
        neg_filter &= ~(truthTable[i] | display[n++]);
    
    // printbits(neg_filter);
    // 진리표에서 1이고 neg_filter에서도 1인것 검출
    if (truthTable[ans] & neg_filter) {
        cout << "ERROR!" << endl;
        return;
    }

    int res = filter & truthTable[ans];
    printbits(res);
}

int main() {
    FASTIO;
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        input();
        solve();
    }

    return 0;
}