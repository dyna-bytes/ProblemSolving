#include <bits/stdc++.h>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define debugVec(v) do { \
    std::cout << "[Debug] ["; \
    for(int i = 0; i < ((v.size())-1); i++) std::cout << v[i] << "|"; \
    std::cout << v[((v.size())-1)] << "]\n"; \
} while(0)
#define debugV2D(v) do { \
    std::cout << "[Debug] [\n"; \
    for(int y = 0; y < (v.size()); y++) { \
        std::cout << "  ["; \
        for(int x = 0; x < ((v[y].size())-1); x++) \
            std::cout << v[y][x] << "|"; \
        std::cout << v[y][(v[y].size())-1] << "]\n"; \
    } \
    std::cout << "]\n"; \
} while(0)
#define endl '\n'
typedef long long ll;
typedef pair<int, int> P;

int N;
vector<int> histogram;

// 분할 정복 [s,e)
int f(int s, int e){
    if(s == e) return 0; // base case: 폭 0
    if(s+1 == e) return histogram[s]; // base case: 폭 1

    int mid = (s+e)/2;
    int res = max(f(s, mid), f(mid, e));

    // time complexity: O(s-e)
    int w = 1, h = histogram[mid], l = mid, r = mid;
    while(r-l+1 < e-s){
        int p = (l > s)? min(h, histogram[l-1]) : -1; 
        int q = (r < e-1)? min(h, histogram[r+1]) : -1;

        if(p >= q){
            h = p;
            l--;
        } else {
            h = q;
            r++;
        }

        res = max(res, ++w * h);
    }
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> N;
    histogram.resize(N+1);
    for(int i = 0; i < N; i++)
        cin >> histogram[i];
    cout << f(0, N);

    return 0;
}