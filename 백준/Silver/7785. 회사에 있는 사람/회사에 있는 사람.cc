#include <bits/stdc++.h>
using namespace std;

struct Compare {
    bool operator() (string left, string right) const
	{
		return left > right;
	}
};

set<string, Compare> nameLog;

int main() {

    int N; cin >> N;
    for (int i = 0; i < N; i++) {
        string name, enter;
        cin >> name >> enter;

        if (enter == "enter") nameLog.insert(name);
        if (enter == "leave") 
            if (nameLog.count(name)) nameLog.erase(name);
    }

    for (string name: nameLog) cout << name << '\n';
}