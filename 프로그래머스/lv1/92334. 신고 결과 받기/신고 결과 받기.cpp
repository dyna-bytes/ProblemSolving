#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

vector<int> solution(vector<string> id_list, vector<string> report, int k) {
    vector<int> answer(id_list.size());
    unordered_map<string, int> id_hash; // {id_이름: id_숫자}
    multimap<string, string> report_map; // {신고자: 피신고자}
    multimap<string, string> rev_report_map; // {피신고자: 신고자}

    int i = 0;
    for (auto str: id_list) id_hash.insert({str, i++});

    for (auto str: report) {
        istringstream ss(str);
        string caller, callee; ss >> caller >> callee;

        bool find = false;
        if (report_map.count(caller)){
            for (auto it = report_map.lower_bound(caller); it != report_map.upper_bound(caller); it++) {
                if (it->second == callee) {
                    find = true; break;
                }   
            }
        }

        if (find) continue;
        report_map.insert({caller, callee});
    }

    string last_caller = "";
    for (auto it: report_map) {
        string caller = it.first;
        string callee = it.second;
        rev_report_map.insert({callee, caller});
        
    }

    for (auto it: rev_report_map) {
        string callee = it.first;
        string caller = it.second;
        if (rev_report_map.count(callee) >= k)
            answer[id_hash.at(caller)]++;
    }

    return answer;
}
