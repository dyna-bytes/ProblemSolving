#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)

int main() {
    FASTIO;
    int N, Q;
    cin >> N >> Q;

    unordered_map<int, string> mId_to_mName;
    unordered_map<string, int> mName_to_mId;

    for (int id = 1; id <= N; id++) {
        string name; cin >> name;

        mId_to_mName.insert({id, name});
        mName_to_mId.insert({name, id});
    }

    for (int i = 0; i < Q; i++) {
        string inp; cin >> inp;
        int id;
        if (inp[0] >= '0' && inp[0] <= '9'){ 
            id = stoi(inp);
            auto it = mId_to_mName.find(id);
            cout << it->second << endl;
        } else {
            auto it = mName_to_mId.find(inp);
            cout << it->second << endl;
        }
    }
}