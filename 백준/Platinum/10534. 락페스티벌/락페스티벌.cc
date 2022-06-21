#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define endl '\n'
typedef long long ll;

struct Vert{
    int x, y1, y2;
    int index;
    Vert(int _x, int _y1, int _y2, int _index){
        x = _x, y1 = _y1, y2 = _y2, index = _index;
    }
};

struct Horiz{
    int y, x1, x2;
    int index;
    Horiz(int _y, int _x1, int _x2, int _index){
        y = _y, x1 = _x1, x2 = _x2, index = _index;
    }
};

struct UnionFind{
    vector<int> parent;
    vector<int> area;
    UnionFind(int N, vector<int>& _area){
        parent.resize(N, -1);
        area = _area;
    }
    int find(int curr){
        if (parent[curr] < 0) return curr;
        return parent[curr] = find(parent[curr]);
    }
    void merge(int a, int b){
        a = find(a);
        b = find(b);
        if (a == b) return;

        if (abs(parent[a]) < abs(parent[b])) swap(a, b);
        area[a] += area[b];
        parent[a] += parent[b];
        parent[b] = a;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N; cin >> N;
    vector<Vert> verticals;
    vector<Horiz> horizontals;
    vector<int> area;
    for(int i = 0; i < N; i++){
        int x, y, w, h; cin >> x >> y >> w >> h;
        
        area.push_back(w*h);
        
        verticals.push_back(Vert(x, y, y+h, i));
        verticals.push_back(Vert(x+w, y, y+h, i));
        
        horizontals.push_back(Horiz(y, x, x+w, i));
        horizontals.push_back(Horiz(y+h, x, x+w, i));
    }

    UnionFind uf(N, area);

    sort(verticals.begin(), verticals.end(), [](Vert& a, Vert& b){
        if (a.x == b.x) return a.y1 < b.y1;
        return a.x < b.x;
    });
    
    // sweep along x-axis
    int prev_y2;
    for(int i = 0; i < verticals.size(); i++){
        if (i > 0 && verticals[i-1].x == verticals[i].x
                && prev_y2 >= verticals[i].y1) {
            prev_y2 = max(prev_y2, verticals[i].y2);
            uf.merge(verticals[i-1].index, verticals[i].index);
        } else
            prev_y2 = verticals[i].y2;
    }

    sort(horizontals.begin(), horizontals.end(), [](Horiz& a, Horiz& b){
        if (a.y == b.y) return a.x1 < b.x1;
        return a.y < b.y;
    });

    // sweep along y-axis
    int prev_x2;
    for(int i = 0; i < horizontals.size(); i++){
        if (i > 0 && horizontals[i-1].y == horizontals[i].y
                && prev_x2 >= horizontals[i].x1) {
            prev_x2 = max(prev_x2, horizontals[i].x2);
            uf.merge(horizontals[i-1].index, horizontals[i].index);
        } else
            prev_x2 = horizontals[i].x2;
    }

    cout << *max_element(uf.area.begin(), uf.area.end());
    
    return 0;
}