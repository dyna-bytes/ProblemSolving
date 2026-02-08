#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define DBG
#ifdef DBG
#define debug(x) cout << "[" << __func__ << "](" << __LINE__ << ") " << #x << " is " << x << endl;
#define debugVect(v) do { \
    cout << "[" << __func__ << "](" << __LINE__ << ") " << #v << " is |\t"; \
    for (auto e: v) cout << e << "|\t" ; \
    cout << endl; \
} while (0)
#define debugVect2d(vv) do { \
    cout << "[" << __func__ << "](" << __LINE__ << ") " << #vv << " is " << endl; \
    for (auto v: vv) debugVect(v); \
} while (0)
#else
#define debug(x)
#define debugVect(v)
#define debugVect2d(vv)
#endif

struct Instruction {
    int var_id; // 매핑된 변수 ID (0 ~ K-1)
    int val;    // 대입할 값
    int thread_id; // 원래 스레드 번호 (출력용, 1-based)
};

class Solution {
public:
    /**
     * @param K 변수의 총 개수 (매핑된 ID는 0 ~ K-1)
     * @param target_values 변수 ID별 최종 목표 값 (크기 K)
     * @param threads 각 스레드의 명령어 스택 (입력 순서대로 저장됨)
     * @return 실행 역순으로 찾은 스레드 번호들 (1-based). 불가능하면 빈 벡터.
     */
    vector<int> solve(int K, vector<int>& target_values, vector<vector<Instruction>>& threads) {
        vector<int> result;

        int total_instructions = 0;
        for (const auto& t : threads) total_instructions += t.size();

        while (result.size() < total_instructions) {
            bool progress = false;

            for (vector<Instruction>& thread: threads) {
                if (thread.empty()) continue;

                Instruction inst = thread.back();
                if (target_values[inst.var_id] == inst.val || target_values[inst.var_id] == 0) {

                    target_values[inst.var_id] = 0;
                    thread.pop_back();
                    result.push_back(inst.thread_id);

                    progress = true;
                }
            }

            if (!progress) return {};
        }

        return result;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t_count;
    if (!(cin >> t_count)) return 0;

    map<string, int> var_name_to_id;
    int var_id_counter = 0;

    vector<vector<Instruction>> threads(t_count);

    for (int i = 0; i < t_count; ++i) {
        int l_i;
        cin >> l_i;
        threads[i].reserve(l_i);

        for (int j = 0; j < l_i; ++j) {
            string token;
            cin >> token;

            size_t eq_pos = token.find('=');
            string name = token.substr(0, eq_pos);
            int val = stoi(token.substr(eq_pos + 1));

            if (var_name_to_id.find(name) == var_name_to_id.end()) {
                var_name_to_id[name] = var_id_counter++;
            }

            threads[i].push_back({var_name_to_id[name], val, i + 1});
        }
    }

    int k_count;
    cin >> k_count;

    vector<int> target_values(k_count);

    for (int i = 0; i < k_count; ++i) {
        string name;
        int val;
        cin >> name >> val;

        int id = var_name_to_id[name];
        target_values[id] = val;
    }

    int total_instructions = 0;
    for (const auto& th : threads) total_instructions += th.size();

    Solution sol;
    // var_id_counter == K
    vector<int> answer = sol.solve(var_id_counter, target_values, threads);

    if (answer.size() != total_instructions) {
        cout << "No" << "\n";
    } else {
        cout << "Yes" << "\n";
        reverse(answer.begin(), answer.end());

        for (int i = 0; i < answer.size(); ++i) {
            cout << answer[i] << (i == answer.size() - 1 ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}