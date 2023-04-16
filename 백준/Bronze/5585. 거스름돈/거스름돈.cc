#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int unit[6] = {500, 100, 50, 10, 5, 1};
int money;

int greedy() {
    int ret = 0;
    for (int i = 0; i < 6; ) {
        if (money < unit[i]) i++;
        else {
            money -= unit[i];
            ret++;
        }
    }
    return ret;
}

int main() {
    cin >> money;
    money = 1000 - money;
    cout << greedy();

    return 0;
}