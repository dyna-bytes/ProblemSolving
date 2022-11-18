#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;
#define endl '\n'
#define MAX 1000001
int A[MAX];

int func(int x){
    if (A[x] != 0) return A[x];
    if (x == 1) return 0;

    int a = MAX, b = MAX, c = MAX;
    if (x % 3 == 0) a = 1 + func(x/3);
    if (x % 2 == 0) b = 1 + func(x/2);
    c = 1 + func(x-1);

    return A[x] = min({a, b, c});
}

void backtracking(int x) {
    if (x == 1) {
        return;
    }

    int a = MAX, b = MAX, c = MAX;
    if (x % 3 == 0) a = 1 + func(x/3);
    if (x % 2 == 0) b = 1 + func(x/2);
    c = 1 + func(x-1);
    int next = min({a, b, c});

    if (next == a) {
        cout << x/3 << " ";
        backtracking(x/3);
    } else if (next == b) {
        cout << x/2 << " ";
        backtracking(x/2);
    } else if (next == c) {
        cout << x - 1 << " ";
        backtracking(x - 1);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);


    int n;
    cin >> n;
    cout << func(n) << endl;
    cout << n << ' ';
    backtracking(n);
    return 0;
}