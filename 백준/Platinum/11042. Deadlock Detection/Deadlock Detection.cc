#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <map>

using namespace std;

// 상태 정의: 잡고 있는 락(held), 원하고 있는 락(want)
struct State {
    int held;
    int want;

    // set 중복 제거를 위한 연산자 오버로딩
    bool operator<(const State& other) const {
        if (held != other.held) return held < other.held;
        return want < other.want;
    }
};

vector<State> candidates;
vector<int> held_by[10]; // held_by[k]: k번 락을 들고 있는 후보들의 인덱스 리스트

int preprocess(const string& s) {
    candidates.clear();
    for(int i=0; i<10; ++i) held_by[i].clear();

    int held_mask = 0;

    for (char c : s) {
        if (c == 'u') {
            held_mask = 0;
            continue;
        }

        int lock = c - '0';

        // 1. Self-Deadlock 체크: 이미 가진걸 또 잡으려 함
        if ((held_mask >> lock) & 1) return -1;

        // 2. 후보 등록: (가진 락) 상태에서 (lock)을 원함
        if (held_mask > 0) {
            candidates.push_back({held_mask, lock});
        }

        held_mask |= (1 << lock);
    }

    sort(candidates.begin(), candidates.end());
    candidates.erase(unique(candidates.begin(), candidates.end(),
        [](const State& a, const State& b){
            return a.held == b.held && a.want == b.want;
        }), candidates.end());

    for (int i = 0; i < candidates.size(); ++i) {
        for (int k = 0; k < 10; ++k) {
            if ((candidates[i].held >> k) & 1) {
                held_by[k].push_back(i);
            }
        }
    }

    return 0;
}

// 의존성 기반 DFS
// current_held: 현재 조합이 가진 락 합집합
// current_want: 현재 조합이 원하는 락 합집합
bool search_deadlock(int current_held, int current_want) {
    // 1. 데드락 판별: 우리가 원하는 모든 것이 우리 안에 있는가?
    if ((current_held & current_want) == current_want) return true;

    // 2. 우리가 지금 '절실하게 필요한(Missing)' 락 찾기
    int missing = current_want & ~current_held;

    // missing이 없다면 위에서 리턴되었을 것임.
    // 최적화: missing 중 아무거나 하나(LSB)를 해결하려고 시도해본다.
    int target_lock = __builtin_ctz(missing); // 0~9 사이 값

    // target_lock을 들고 있는 후보들을 호출
    for (int next_idx : held_by[target_lock]) {
        const State& next_cand = candidates[next_idx];

        // 자원 충돌(Disjoint) 체크: 이미 가진 락과 겹치면 안 됨
        if ((current_held & next_cand.held) == 0) {
            if (search_deadlock(current_held | next_cand.held, current_want | (1 << next_cand.want))) {
                return true;
            }
        }
    }

    return false;
}

void solve() {
    int n;
    while (cin >> n && n != 0) {
        string s;
        cin >> s;

        if (preprocess(s) == -1) {
            cout << "UNSAFE" << endl;
            continue;
        }

        bool unsafe = false;

        for (const auto& start_node : candidates) {
            if (search_deadlock(start_node.held, 1 << start_node.want)) {
                unsafe = true;
                break;
            }
        }

        if (unsafe) cout << "UNSAFE" << endl;
        else cout << "SAFE" << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}