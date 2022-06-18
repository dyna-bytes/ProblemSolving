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
    Point(int _x, int _y1, int _y2, bool _start){
        x = _x, y1 = _y1, y2 = _y2, start = _start;
    }
};

struct SegTree{
    int size;
    vector<int> count; // count is used for marking all the Y points in the range
    vector<int> segtree;
    SegTree(int n){
        size = 1;
        while(size < n) size *= 2;
        size *= 2;
        count.resize(size);
        segtree.resize(size);
    }

    // update count by marking Y region
    void mark_count(int s, int e, int val){
        int l = s + size/2 - 1; // y를 one base index로 관리한다.
        int r = e + size/2 - 1; 

        for(int i = l; i <= r; i++)
            count[i] += val;   
    }

    // construct segtree with Y region
    void construct(int s, int e, int val = 1){
        int l = s + size/2 - 1; // y를 one base index로 관리한다.
        int r = e + size/2 - 1;

        // leaf node initialization
        for(int i = l; i <= r; i++)
            if(count[i]) segtree[i] = val;
            else segtree[i] = 0;

        // construct segtree in O(n)
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

        // y를 one base index로 관리한다.
        points.push_back(Point(x1, y1+1, y2+1, true));
        points.push_back(Point(x2, y1+1, y2+1, false));
    }

    sort(points.begin(), points.end(), [](Point& a, Point& b) {
        return a.x < b.x;        
        });

    int answer = 0;
    SegTree ST(30002);
    for(int i = 0; i < points.size(); i++){
        if(i > 0)
            answer += (points[i].x - points[i-1].x) * ST.segtree[1];
        ST.mark_count(points[i].y1, points[i].y2 - 1, points[i].start ? 1 : -1);      
        ST.construct(points[i].y1, points[i].y2 - 1);
    }

    cout << answer;
    return 0;
}