#include <bits/stdc++.h>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define debugVec(v) do { \
    std::cout << "[Debug] ["; \
    for(ll i = 0; i < ((v.size())-1); i++) std::cout << v[i] << "|"; \
    std::cout << v[((v.size())-1)] << "]\n"; \
} while(0)
#define debugV2D(v) do { \
    std::cout << "[Debug] [\n"; \
    for(ll y = 0; y < (v.size()); y++) { \
        std::cout << "  ["; \
        for(ll x = 0; x < ((v[y].size())-1); x++) \
            std::cout << v[y][x] << "|"; \
        std::cout << v[y][(v[y].size())-1] << "]\n"; \
    } \
    std::cout << "]\n"; \
} while(0)
#define endl '\n'
typedef long long ll;
typedef pair<ll, ll> P;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    ll N, M; cin >> N >> M;
    vector<ll> plan(M); // plan[m]: m번째 날에 가기로 한 역
    vector<ll> ticket(N); // ticket[i]: i<->i+1역으로 티켓을 통해 이동할 때의 비용. one based index
    vector<ll> card_passing(N); // card_passing[i]: i<->i+1역으로 카드를 통해 이동할 때의 비용. one based index
    vector<ll> card(N); // card[i]: i역을 통과할 때 사야하는 카드의 비용. one based index

    for (ll i = 0; i < M; i++)  
        cin >> plan[i];
    
    for (ll i = 1; i < N; i++) 
        cin >> ticket[i] >> card_passing[i] >> card[i];

    vector<ll> count(N+1); // count[i]: i<->i+1역을 통과한 누적 횟수
    for (ll i = 0; i < M-1; i++) {
        if (plan[i] < plan[i+1]) {
            count[plan[i]]++; // 출발지
            count[plan[i+1]]--; // 도착지
        } else {
            count[plan[i+1]]++; 
            count[plan[i]]--;
        }
    }

    for (ll i = 1; i <= N; i++)
        count[i] += count[i-1];

    // debugVec(count);

    ll res = 0;
    for (ll i = 1; i < N; i++) {
        if (count[i] > 0) 
            res += min(ticket[i]*count[i], card_passing[i]*count[i] + card[i]);
    }

    cout << res;
    
    return 0;
}