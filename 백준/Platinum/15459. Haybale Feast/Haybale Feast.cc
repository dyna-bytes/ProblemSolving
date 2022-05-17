#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define endl '\n'
typedef long long ll;

ll N, M;
vector<ll> flavor, spiciness;

/**
 * @brief Parametric search로 조건을 만족하는 매운맛 허들을 찾기위해 이분탐색함
 * 
 * 조건1. 연속인 열일 것
 * 조건2. flavor의 합이 M 이상일 것
 * 
 * 문제: 조건을 만족하는 열의 최대 매운맛 중 최솟값을 찾을 것.
 * 조건을 확인하는 함수를 Maximum Subarray(최대 부분배열합) 문제와 비슷하게 구현한다.
 */

bool check(ll spicyHurdle){
    ll contiguousFlavorSum = 0;
    for(ll i = 0; i < N; i++){
        if(spiciness[i] > spicyHurdle){
            // 매운맛 조건을 못 만족시켜 열이 끊어졌다면 연속합을 초기화 한다.
            contiguousFlavorSum = 0;
        }else{
            contiguousFlavorSum += flavor[i];

            // 조건을 만족한다면 바로 리턴한다.
            if(contiguousFlavorSum >= M) return true;
        }
    }
    return false;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> N >> M;
    flavor.resize(N); 
    spiciness.resize(N);

    ll lo = 0, hi = 0;
    for(ll i = 0; i < N; i++){
        cin >> flavor[i] >> spiciness[i];
        hi = max(hi, spiciness[i]);
    }

    while(lo + 1 < hi){
        ll mid = (lo + hi)/2;
        
        if(check(mid)) hi = mid;
        else lo = mid;
    }
    cout << hi;


    return 0;
}