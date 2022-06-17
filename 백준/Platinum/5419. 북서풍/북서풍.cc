#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define endl '\n'
typedef long long ll;
typedef pair<int, int> P;
const int INF = 1e9 + 1;

struct SegTree{
    int size;
    vector<int> node;
    SegTree(int n){
        size = 1;
        while(size < n) size *= 2;
        size *= 2;
        node.resize(size + 1);
    }
    void insert(int idx, int val=1){
        idx += size/2;
        node[idx] += val;
        idx /= 2;
        while(idx > 0){
            node[idx] = node[idx*2] + node[idx*2 + 1];
            idx /= 2;
        }
    }
    // sum in range[s, e]
    int sum(int s, int e){
        int l = s + size/2;
        int r = e + size/2;
        
        int ret = 0;
        while(l <= r){
            if(l % 2) ret += node[l++];
            if(!(r % 2)) ret += node[r--];
            l /= 2;
            r /= 2;
        }
        return ret;
    }
};

class Solve{
public:
    ll northWesternWinds(int N, vector<P>& points){
        // 좌표압축
        // 1. y좌표 순으로 오름차순 정렬
        sort(points.begin(), points.end(), [](P& a, P& b){
            return a.second < b.second;
        });

        // 2. y좌표에 대해 좌표압축
        int range = 0;
        vector<int> newY(N);
        for(int i = 0; i < N; i++){
            if(i > 0 && points[i].second > points[i-1].second) range++;
            newY[i] = range;
        }

        // 3. 압축된 y좌표를 원래 배열에 재삽입
        for(int i = 0; i < N; i++)
            points[i].second = newY[i];

        
        // x좌표를 오름차순으로, x좌표 값이 같다면 y좌표를 내림차순으로 정렬
        sort(points.begin(), points.end(), [](P& a, P& b){
            if(a.first == b.first) return a.second > b.second;
            return a.first < b.first;
        });

        SegTree tree(N);
        ll ret = 0;
        // x좌표에 대해 왼쪽에서 오른쪽으로, x좌표가 같다면 y좌표가 큰 쪽에서 작은 쪽으로 스위핑
        for(P point: points){
            // x좌표가 자기보다 같거나 작고, y좌표가 자기보다 큰 왼쪽 상단 직사각형 구간 내의 점의 개수
            ret += tree.sum(point.second, range);
            tree.insert(point.second);
        }
        return ret;
    }
};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int T; cin >> T;
    while(T--){
        int N; cin >> N;
        vector<P> points(N);
        for(int i = 0; i < N; i++)
            cin >> points[i].first >> points[i].second; // {x, y}
        
        Solve sol;
        cout << sol.northWesternWinds(N, points) << endl; 
    }
    return 0;
}