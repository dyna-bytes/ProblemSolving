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
const int MAX = 300001;

struct s_node{
    P line;
    int prev_top;
    bool cont;
    s_node(P _line, int _prev_top, int _cont){
        line = _line, prev_top = _prev_top, cont = _cont;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N; cin >> N;    
    vector<P> circles(N);

    for(int i = 0; i < N; i++){
        int x, r; cin >> x >> r;
        circles[i] = {x - r, x + r};
    }

    sort(circles.begin(), circles.end(), [](P& a, P& b){
        if(a.first == b.first) return a.second > b.second;
        return a.first < b.first;
    });

    int ret = 0;
    stack<s_node> S;
    S.push({{-INF, -INF}, 0, false});

    for(int i = 0; i < N; i++){
        while(!S.empty() && (circles[S.top().prev_top].second <= circles[i].first)){
            ret++;
            
            if(circles[S.top().prev_top].second == S.top().line.first) ret++;
            S.pop();
        }

        if(!S.empty() && S.top().cont && S.top().line.first == circles[i].first)
            S.top().line.first = circles[i].second;
        else if(!S.empty())
            S.top().cont = false;
        
        S.push({circles[i], i, true});
    }

    while(!S.empty()){
        ret++;
        if(S.top().line.first == circles[S.top().prev_top].second)
            ret++;
        S.pop();
    }


    cout << ret;
    return 0;
}