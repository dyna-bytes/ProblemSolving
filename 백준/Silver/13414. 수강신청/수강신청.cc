#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
typedef pair<string, int> psi;

int main(){
    fastio;
    int K, L; 
    cin >> K >> L;

    unordered_map<string, int> hash;
    for (int i = 0; i < L; i++) {
        string num; cin >> num;

        hash[num] = i;
    }

    vector<psi> v(hash.begin(), hash.end());
    sort(v.begin(), v.end(), [](psi& p1, psi& p2){
        return p1.second < p2.second;
    });

    for (int i = 0; i < K && i < v.size(); i++) cout << v[i].first << endl;

    return 0;
}