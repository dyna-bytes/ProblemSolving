#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define endl '\n'
typedef long long ll;

vector<ll> A;
ll cnt = 0;

vector<ll> merge(vector<ll> arr1, vector<ll> arr2){
    vector<ll> ret;
    ll p1, p2;
    for(p1 = 0, p2 = 0; p1 < arr1.size() && p2 < arr2.size(); ){
        if(arr1[p1] <= arr2[p2]){
            ret.push_back(arr1[p1++]);
        }else{
            ret.push_back(arr2[p2++]);
            cnt += (arr1.size() - p1);
        }
    }

    if(p1 == arr1.size() && p2 < arr2.size())
        while(p2 < arr2.size()) ret.push_back(arr2[p2++]);
    if(p1 < arr1.size() && p2 == arr2.size())
        while(p1 < arr1.size()) ret.push_back(arr1[p1++]);
    return ret;
}

vector<ll> divide(ll s, ll e){
    if(s == e) return {A[s]};

    ll mid = (s + e)/2;
    return merge(divide(s, mid), divide(mid+1, e));
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll N; cin >> N;
    A.resize(N);
    for(ll i = 0; i < N; i++)
        cin >> A[i];

    vector<ll> ret = divide(0, N-1);
    // for(ll i : ret) cout << i << " ";
    cout << cnt;
    return 0;
}