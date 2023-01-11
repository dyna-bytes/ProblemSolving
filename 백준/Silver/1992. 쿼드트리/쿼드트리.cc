#include <iostream>
#include <vector>
using namespace std;

int N;
vector<vector<int>> A;

bool allSame(int y1, int x1, int y2, int x2){
    int type = A[y1][x1];
    for(int y = y1; y <= y2; y++)
        for(int x = x1; x <= x2; x++)
            if(A[y][x] != type) return false;
    return true;
}

string quadTree(int y1, int x1, int y2, int x2){
    if(allSame(y1, x1, y2, x2)){
        int type = A[y1][x1];
        return type ? "1" : "0";
    }

    string ret = "(";
    int divY = (y2 - y1 + 1)/2, divX = (x2 - x1 + 1)/2;
    for(int y = y1; y <= y2; y += divY)
        for(int x = x1; x <= x2; x += divX){
            int ny = min(y + divY - 1, y2), nx = min(x + divX - 1, x2);
            ret += quadTree(y, x, ny, nx);
        }
    ret += ")";
    return ret;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N;
    A.resize(N, vector<int>(N));

    for(int y = 0; y < N; y++){
        string buf; cin >> buf;
        for(int x = 0; x < N; x++)
            A[y][x] = buf[x] - '0';
    }

    string ret = quadTree(0, 0, N-1, N-1);
    cout << ret;
    return 0;
}