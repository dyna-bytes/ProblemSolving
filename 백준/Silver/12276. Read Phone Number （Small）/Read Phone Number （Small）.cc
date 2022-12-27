#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define debug(x) cout << "[debug] " << #x << " is " << x << endl
#define debugVec(v) do{\
    cout << "[debug] " << #v << endl;\
    for (auto e: v) cout << e << " | ";\
    cout << endl;\
}while(0)
typedef pair<int, int> pii;
typedef vector<int> vint;
typedef vector<pii> vpii;

const string numbers[] = {
    "zero", "one", "two", 
    "three", "four", "five", 
    "six", "seven", "eight", 
    "nine"
};
const string rules[] = {
    "",    "",    "double",
    "triple",    "quadruple",    "quintuple",
    "sextuple",    "septuple",    "octuple",
    "nonuple",    "decuple"
};

int n;
int f;
vint nums(11);
vint format(11);
vint p_sum(12);
vpii res(11);

void solve() {
    int r = -1;
    for (int p = 0; p < p_sum.size() - 1; p++) {
        int prev = -1;
        for (int i = p_sum[p]; i < p_sum[p + 1]; i++) {
            if (prev == nums[i]) res[r].second++;
            else {
                prev = nums[i];
                res[++r] = {nums[i], 1};
            }
        }
    }

    for (int i = 0; i <= r; i++) {
        auto& [num, cnt] = res[i];
        if (cnt > 10) while (cnt--) cout << numbers[num] << " ";        
        else if (cnt > 1) cout << rules[cnt] << " " << numbers[num] << " ";
        else cout << numbers[num] << " ";
    }
    cout << endl;
}

int main() {
    FASTIO;
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        string N, F; cin >> N >> F;
        nums = {}; format = {};
        p_sum = {}; res = {};

        nums.resize(N.size());
        res.resize(N.size());

        for (int i = 0; i < N.size(); i++)
            nums[i] = N[i] - '0';
        
        int f = 0;
        istringstream iss(F);
        string buffer;
        while (getline(iss, buffer, '-')) 
            format.push_back(stoi(buffer));
        
        p_sum.resize(format.size() + 1);
        for (int i = 0; i < format.size(); i++)
            p_sum[i + 1] = p_sum[i] + format[i];

        cout << "Case #" << (t + 1) << ": ";
        solve();
    }
    return 0;
}