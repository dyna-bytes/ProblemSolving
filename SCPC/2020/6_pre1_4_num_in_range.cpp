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

/**
 * 문제해석:
 * 1. 원래의 수를 k길이씩 잘라서 N-k+1개의 수를 얻는다.
 * 2. 주어진 길이 m에 대해, 정수 a를 마음대로 골라 N-k+1개의 수들 중
 *   [a, a+m] 구간에 포함된 수가 몇 개인지 센다. 이때 최대 포함된 개수를 X라 하자.
 * 3. 숫자를 바꿀 위치를 잘 선택해서 (또는 바꾸지 않고) X를 최대화 한다.
 * 
 * 관찰:
 * 1. 숫자 하나를 1로 바꿀 때, N-k+1의 수들 중 바뀌는 수는 바뀌는 숫자를 포함하고 있는 k개의 수이다.
 * 2. 원래의 수의 길이가 N이므로 총 N개의 숫자를 1로 바꿔볼 수 있다.
 * 따라서 바뀌는 수의 총 개수는 Nk개이다.
 * 3. 길이가 m인 구간에 가장 많이 포함시킬 수 있는 수의 개수, 즉 X를 구할 수 있는 자료 구조가 필요
 *
 * 문제변형:
 * 1. N-k+1개의 수들이 주어졌을 때, 구간 [a, a+m]에 포함된 수들의 최대 포함 개수 X를 어떻게 구하는가?
 * 2. 각각의 수는 구간으로, 각각의 구간은 점으로 바꾸어 보자!
 * 3. 즉, 어떤 수 x는 구간 [x, x+m]으로, 수 x들을 포함하는 구간 [a, a+m]은 점 a로 바꾼다.
 * 4. 어떤 수 x가 나타날 때 마다 구간 [x, x+m]에 모조리 +1을 해주면, 
 *  구간이 여러번 겹친 점 a에는 구간이 겹친 횟수가 기록될 것이고, 
 *  이는 해당 점 a에서 범위 집합 x ㅌ [a-m, a] 에 속한 수 x들의 개수와 동치이다.
 * 5. 즉, 각 점 a (구간 [a-m, a]에 포함된 수 x의 개수) 의 값 중 최댓값을 얻으면 된다.
 * 6. 숫자를 1로 바꾸는 작업을 할 때마다, 숫자가 나타나는 쿼리와 숫자를 제거하는 쿼리를 돌리며 최대 a값을 찾자.
 */

struct LazyProp{
    int size = 1;
    int N;
    vector<int> lazy, segtree;
    LazyProp(int n){
        N = n;
        while(size < n) size *= 2;
        size *= 2;
        lazy.resize(size+1);
        segtree.resize(size+1);
    }
    void prop(int node){
        if (lazy[node] == 0) return; 
        if (node < size/2) {
            lazy[node*2] += lazy[node];
            lazy[node*2+1] += lazy[node];
        }
        segtree[node] += lazy[node];
        lazy[node] = 0;
    }
    // add val to range [s, e). 구간에 수를 더하는 쿼리
    void update(int s, int e, int val){ update(1, 0, size/2, s, e, val); }
    void update(int node, int ns, int ne, int s, int e, int val){
        prop(node);
        if (e <= ns || ne <= s) return;
        if (s <= ns && ne <= e) {
            lazy[node] += val;
            prop(node);
            return;
        }
        int mid = (ns+ne)/2;
        update(node*2, ns, mid, s, e, val);
        update(node*2+1, mid, ne, s, e, val);
        segtree[node] = max(segtree[node*2], segtree[node*2+1]);
    }
    // get max in range [s, e). 구간에서 최댓값을 찾는 쿼리
    int query(int s, int e){ return query(1, 0, size/2, s, e); }
    int query(int node, int ns, int ne, int s, int e){
        prop(node);
        if (e <= ns || ne <= s) return INT_MIN;
        if (s <= ns && ne <= e) return segtree[node];
        int mid = (ns+ne)/2;
        return max(query(node*2, ns, mid, s, e), query(node*2+1, mid, ne, s, e));
    }
    int getmax(){ 
        prop(1);
        return segtree[1];
    }
};

void solve(){
    int N, K, M; cin >> N >> K >> M;
    string str; cin >> str;

    auto num = [&](int i){ // 위치 i부터 길이가 K인 부분 문자열을 만드는 람다식
        int res = 0;
        for(int j = K - 1, t = 1; j >= 0; j--, t *= 10)
            res += t * (str[i + j] - '0');
        return res;
    };

    vector<int> v; // 각 부분 문자열들을 저장
    for(int i = 0; i <= N - K; i++) v.push_back(num(i));

    vector<vector<int>> old_v(N), new_v(N); 
    vector<int> total = v;
    for(int i = 0; i < N; i++){
        if (str[i] == '1') continue;

        // old_v는 i번째 숫자가 1로 바뀌기 전의 원래 값들을 저장한다.
        for(int j = 0; j < K && i - j >= 0; j++) // 각 i에 대해, i보다 앞선 i-j 위치에서 시작하고 길이가 K인 부분 문자열들을 저장
            if (i - j <= N - K) old_v[i].push_back(v[i - j]);

        char temp = '1';
        swap(str[i], temp);

        // i번째 숫자가 1로 바뀐 상황에서 new_v는 영향을 받을 수 있는 최대 K개의 수들을 저장한다.
        for(int j = 0; j < K && i - j >= 0; j++) // i번째 수가 1로 바뀐 상태에서, i보다 앞선 위치에서 시작하고 길이가 K인 부분 문자열들을 저장
            if (i - j <= N - K) new_v[i].push_back(num(i - j));
        
        swap(str[i], temp);
        for(int x: new_v[i]) total.push_back(x);
    }

    sort(total.begin(), total.end()); // 각 부분 문자열 x를 구간 [x, x+m]을 대표하는 점으로 삼고 좌표압축하여 세그트리의 리프노드로 삼음
    total.erase(unique(total.begin(), total.end()), total.end()); 

    LazyProp Seg(total.size());

    auto update = [&](int x, int val) { // 숫자 x에 해당하는 위치를 찾아 구간 [x, x+m]에 val을 더함
        int s = lower_bound(total.begin(), total.end(), x) - total.begin();
        int e = upper_bound(total.begin(), total.end(), x + M) - total.begin();
        Seg.update(s, e, val); // 여러 구간 [x, x+m], [y, y+m], [z, z+m] 등이 겹치면 겹친 횟수 만큼 리프노드 a의 값이 증가할 것이다.
    };

    // 수 x가 포함될 수 있는 구간에 x가 추가되면 +1, 제거되면 -1
    for(int x: v) update(x, 1); // 일단 숫자 x들을 모두 추가해본다.

    int ans = Seg.getmax(); // 세그트리의 각 리프노드 a는 구간 [a-m, a]에 포함된 x의 개수를 의미한다.
    
    for(int i = 0; i < N; i++){ // 각 i번째 숫자를 1로 바꾼 경우에 대해
        for(int x: old_v[i]) update(x, -1); // 이전에 추가된 숫자들을 제거하고
        for(int x: new_v[i]) update(x, 1); // 바뀐 숫자들을 추가한다.
        ans = max(ans, Seg.getmax());
        for(int x: old_v[i]) update(x, 1);
        for(int x: new_v[i]) update(x, -1);
    }
    
    cout << ans << endl;
};

int main(int argc, char** argv){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int T, test_case;

    cin >> T;
    for(test_case = 0; test_case  < T; test_case++){
        
        cout << "Case #" << test_case+1 << endl;
        solve();
    }

    return 0;
}