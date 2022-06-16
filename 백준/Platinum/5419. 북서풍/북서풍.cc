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

/**
 * @brief y축에 평행인 선분을 왼쪽에서 오른쪽으로 스위핑하며
 * 이전의 점에서 현재 점으로 올 수 있는 모든 점의 개수를 더한다.
 * 
 * 규칙1: 이번 점으로 항해할 수 있는 점은 이미 방문한 점들 중에만 있다.
 * 규칙2: 이미 방문한 점들 중, y좌표가 현재 점보다 크거나 같은 점만 방문할 수 있다.
 * 규칙 종합: 현재 점P에 대해 y >= P.y 인 y좌표를 갖는 점의 개수를 세어야 한다.
 * 
 */

struct SegTree{
    int N, size;
    vector<int> tree;
    SegTree(int n){
        N = n;
        size = 1;
        while(size < N) size *= 2;
        size *= 2;
        tree.resize(size);
    }

    void update(int idx, int val = 1){
        int curr = idx + size/2;

        tree[curr] += val;
        curr /= 2;
        while(curr > 0){
            tree[curr] = tree[curr*2] + tree[curr*2 + 1];
            curr /= 2;
        }
    }

    void inc(int idx){
        idx += size/2;
        while(idx){
            tree[idx]++;
            idx/=2;
        }
    }

    // 구간 [s, e]의 합
    int sum(int s, int e){
        int l = s + size/2;
        int r = e + size/2;
        int ret = 0;
        while(l <= r){
            if(l % 2) ret += tree[l++];
            if(!(r % 2)) ret += tree[r--];
            l /= 2;
            r /= 2;
        }
        return ret;
    }
};

void solve(){
    int N; cin >> N;
    SegTree ST(N);
    vector<P> points(N);
    for(int i = 0; i < N; i++){
        int x, y; cin >> x >> y;
        points[i] = {x, y};
    }

    // 점들을 y좌표 순으로 정렬
    sort(points.begin(), points.end(), 
        [](P& a, P& b){ 
            return a.second < b.second; 
        });
    
    // 서로 구분되는 y좌표 개수를 세며 y좌표 재설정
    // [-1e9, 1e9] -> [0, N-1] 로 y좌표 범위를 압축함
    int range = 0;
    vector<int> newY(N);
    for(int i = 0; i < N; i++){
        if(i > 0 && points[i].second != points[i-1].second) range++;
        newY[i] = range;
    }

    for(int i = 0; i < N; i++)
        points[i].second = newY[i];

    // 점들을 다시 x좌표 순으로, x좌표가 같다면 y좌표가 작아지는 순으로 정렬
    sort(points.begin(), points.end(), 
        [](P& a, P& b){
            if(a.first == b.first) return a.second > b.second;
            return a.first < b.first;
        });

    // 정렬된 기준에 따라 x좌표를 작은 값부터 큰 값으로 스위핑하며
    // 현재 점으로 올 수 있는 점의 개수를 센다.
    ll res = 0;
    for(int i = 0; i < N; i++){
        // x < P.x 이고, y ㅌ [P.y, max y] 인 범위 내의 점의 개수를 더함
        res += ST.sum(points[i].second, ST.size/2 - 1);
        ST.update(points[i].second);
    }

    cout << res << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int T; cin >> T;
    while(T--)
        solve(); 
    
    return 0;
}