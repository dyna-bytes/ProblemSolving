#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define endl '\n'
typedef long long ll;

int cross(int x1, int y1, int x2, int y2){
    return x1*y2 - x2*y1;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int x1, y1, x2, y2, x3, y3;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    int vec_cross = cross(x2 - x1, y2 - y1, x3 - x2, y3 - y2);
    if(vec_cross > 0) cout << 1;
    else if(vec_cross < 0) cout << -1;
    else cout << 0;
    
    return 0;
}