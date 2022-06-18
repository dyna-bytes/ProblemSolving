#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define endl '\n'
typedef long long ll;

struct Point{
    int x, y1, y2;
    bool start;
};

struct SegTree{
    int size;
    vector<int> count; // count is Binary Search Tree used to mark all the Y points in the range
    vector<int> segtree;
    SegTree(int n){
        size = 1;
        while(size < n) size *= 2;
        size *= 2;
        count.resize(size);
        segtree.resize(size);
    }
    // update count by marking Y region
    void update(int s, int e, int val){
        int l = s + size/2 - 1;
        int r = e + size/2 - 1;

        for(int i = l; i <= r; i++)
            count[i] += val;   
    }
    // insert segtree with Y region
    void insert(int s, int e, int val = 1){
        int l = s + size/2 - 1;
        int r = e + size/2 - 1;

        for(int i = l; i <= r; i++)
            if(count[i]) segtree[i] = val;
            else segtree[i] = 0;

        for(int i = size/2-1; i > 0; i--)
            segtree[i] = segtree[i*2] + segtree[i*2 + 1];
    } 
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N; cin >> N;
    vector<Point> points;

    for (int i = 0; i < N; i++) {
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        Point temp;
        temp.y1 = y1 + 1, temp.y2 = y2 + 1;
        temp.x = x1, temp.start = true;
        points.push_back(temp);
        temp.x = x2, temp.start = false;
        points.push_back(temp);
    }

    sort(points.begin(), points.end(), [](Point& a, Point& b) {
        return a.x < b.x;        
        });

    int answer = 0;
    SegTree ST(30002);
    for(int i = 0; i < points.size(); i++){
        if(i > 0)
            answer += (points[i].x - points[i-1].x) * ST.segtree[1];
        ST.update(points[i].y1, points[i].y2 - 1, points[i].start ? 1 : -1);      
        ST.insert(points[i].y1, points[i].y2 - 1);
    }

    cout << answer;
    return 0;
}