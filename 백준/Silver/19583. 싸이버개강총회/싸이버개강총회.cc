#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
typedef vector<int> vint;

map<string, bool> table;

int convert_time(string& str_time) {
    return stoi(str_time.substr(0, 2)) * 60 + stoi(str_time.substr(3, 2));
}

int S, E, Q;

int main() {
    string str_S, str_E, str_Q;
    cin >> str_S >> str_E >> str_Q;

    S = convert_time(str_S);
    E = convert_time(str_E);
    Q = convert_time(str_Q);

    int cnt = 0;
    string str_time, name;
    while (!cin.eof()) {
        cin >> str_time >> name;
        int time = convert_time(str_time);
        
        if (time <= S) table[name] = true;
        else if (E <= time && time <= Q && table[name]) {
            cnt++;
            table[name] = false;
        }
    }
    cout << cnt;

    return 0;
}