// based on https://www.acmicpc.net/source/42052305
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define debug(x) cout << "[debug] " << #x << " is " << x << endl
#define debugIter(v) do{\
    cout << "[debug] " << #v << endl;\
    for (auto e: v) cout << e << " | ";\
    cout << endl;\
}while(0)
#define debutIter2D(vv) do{\
    cout << "[debug] " << #vv << endl;\
    for (auto v: vv) {\
        for (auto e: v) cout << e << " | ";\
        cout << endl;\
    }\
    cout << endl;\
}while(0)
typedef pair<int, int> pii;
typedef vector<int> vint;
typedef vector<pii> vpii;
typedef vector<string> vstr;

/**
 *  --     A
 * |  |  F   B
 *  --     G
 * |  |  E   C
 *  --     D
 */
const vstr SEVEN_SEGMENT = {
    "1111110", // 0
    "0110000", // 1
    "1101101", // 2
    "1111001", // 3
    "0110011", // 4
    "1011011", // 5
    "1011111", // 6
    "1110000", // 7
    "1111111", // 8
    "1111011"  // 9
};

int N;
vstr input;

void get_input() {
    cin >> N;
    input = {}; input.resize(N);
    for (auto& str: input) cin >> str;
}

vstr generate_cand(int start) {
    vint broken(7);
    vint functional(7);
    int x = start; // the number x : 0~9
    for (const string& nth_element: input) {
        // compare with LUT
        const string& ORIGINAL = SEVEN_SEGMENT[x];
        for (int i = 0; i < 7; ++i) {
            if (nth_element[i] == '0' && ORIGINAL[i] == '1') broken[i] = true;
            else if (nth_element[i] == '1' && ORIGINAL[i] == '0') return {};
            else if (nth_element[i] == '1') functional[i] = true;
        }
        x = (x + 9) % 10;
    }

    x = start;
    for (const string& nth_element: input) {
        // check again
        const string& ORIGINAL = SEVEN_SEGMENT[x];
        for (int i = 0; i < 7; ++i) {
            if (nth_element[i] == '1' && broken[i]) return {};
            else if (nth_element[i] == '0' && ORIGINAL[i] == '1' && functional[i]) return {};
        }
        x = (x + 9) % 10;
    }

    string next_nth = SEVEN_SEGMENT[x]; // get the n+1'th element
    for (int i = 0; i < 7; ++i) 
        if (broken[i]) next_nth[i] = '0';
    
    vstr ret;
    for (int all_possibility = 0; all_possibility <= 0b1111111; ++all_possibility) {
        string cand = next_nth;
        
        // generate candidates based on the every possibilities
        for (int i = 0; i < 7; ++i) 
            if (all_possibility && (1 << i)) 
                if (broken[i]) cand[i] = '0';

        ret.push_back(cand);
    }

    sort(ret.begin(), ret.end());
    ret.erase(unique(ret.begin(), ret.end()), ret.end());
    return ret;
}

string solve() {
    vstr candidates;
    // try each number from 0 to 9
    for (int start = 0; start < 10; ++start) {
        vstr cand = generate_cand(start);
        if (cand == vstr{}) continue;

        for (const string& c: cand) candidates.push_back(c);
    }

    sort(candidates.begin(), candidates.end());
    candidates.erase(unique(candidates.begin(), candidates.end()), candidates.end());
    return (candidates.size() == 1 ? candidates[0] : "ERROR!");
}

int main() {
    FASTIO;
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": "; 
        get_input();
        cout << solve() << endl;
    }
    return 0;
}