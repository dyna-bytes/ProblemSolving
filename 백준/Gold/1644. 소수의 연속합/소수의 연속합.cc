#include <bits/stdc++.h>
using namespace std;
#define debug(x) std::cout << "[debug] " << #x << " is " << x << '\n'
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
typedef vector<int> vint;

vint isPrime;
vint prime;

void Erathose(int N) {
    isPrime.resize(N+1, true);
    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i <= N; i++) {
        for (int j = i*2; j <= N; j += i)  
            isPrime[j] = false;
    }

    for (int i = 2; i <= N; i++)
        if (isPrime[i]) prime.push_back(i);
}

int twoPointer(int N) {
    int ret = 0;
    int sum = 0;

    
    int s = 0, e = 0;
    for (; e < prime.size(); ) {
        if (sum < N) sum += prime[e++];
        else if (sum >= N) {
            if (sum == N) ret++;
            sum -= prime[s++];
        }
    }

    for (; s < prime.size(); ) {
        if (sum == N) ret++;
        sum -= prime[s++];
    }

    return ret;
}

int main() {
    fastio;
    
    int N; cin >> N;
    Erathose(N);

    cout << twoPointer(N);
    return 0;
}