#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define debug(x) cout << "[debug] " << #x << " is " << x << endl
typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<pll> vpll;
#define PRICE first
#define COUPON second

ostream& operator<< (ostream &cout, pll& p) {
    cout << "{" << p.first << ", " << p.second << "}";
}

int N, K;
ll M;
vpll cows;

ll solve() {
    sort(cows.begin(), cows.end(), [](pll& p1, pll& p2) {
        if (p1.COUPON == p2.COUPON) return p1.PRICE < p2.PRICE;
        return p1.COUPON < p2.COUPON;
    });

    priority_queue<pll, vpll, greater<pll>> boughtWithCoupon; // 구매한 소를 일반가 순으로 오름차순 정렬
    boughtWithCoupon.push({ LLONG_MAX, LLONG_MAX });

    ll cow_count = 0;
    ll money = 0;
    for (pll& cow: cows) {
        if (K > 0) {
            if (money + cow.COUPON > M) continue;
            money += cow.COUPON;
            boughtWithCoupon.push(cow);
            cow_count++;
            K--;
            continue;
        }
        
        pll candidate = boughtWithCoupon.top();
        if (cow.PRICE > cow.COUPON + candidate.PRICE - candidate.COUPON) {
            if (money + cow.COUPON + candidate.PRICE - candidate.COUPON > M) continue;
            money += cow.COUPON + candidate.PRICE - candidate.COUPON;
            boughtWithCoupon.pop();
            boughtWithCoupon.push(cow);
            cow_count++;
        } else {
            if (money + cow.PRICE > M) continue;
            money += cow.PRICE;
            cow_count++;
        }
    }
    return cow_count;
}

int main() {
    FASTIO;
    cin >> N >> K >> M;
    cows.resize(N);
    for (auto& [price, coupon]: cows) cin >> price >> coupon;
    cout << solve();
    return 0;
}