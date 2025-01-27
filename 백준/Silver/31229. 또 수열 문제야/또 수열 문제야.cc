#include <bits/stdc++.h>
#define FASTIO cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(0)
#define _MAX 5000
using namespace std;

vector<uint64_t> odds;
void getOdds(int N) {
    for (int i = 0; odds.size() < N; i++)
        odds.push_back(i*2 + 1);
}

int main() {
    int N;
    cin >> N;
    odds.reserve(N);

    getOdds(N);

    for (auto elem: odds)
        cout << elem << ' ';

    return 0;
}