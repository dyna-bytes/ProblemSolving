#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> P;
typedef tuple<int, int, int> T;
struct Record{
    int time;
    int car_num;
    bool in;
    Record(int t, int n, bool i){
        time = t, car_num = n, in = i;
    }
};

int time_convert(string inp){ // "12:34" -> 12*60 + 34
    string s_hour = inp.substr(0, 2);
    string s_minute = inp.substr(3, 5);
    return stoi(s_hour) * 60 + stoi(s_minute);
}

int fee_convert(int time, vector<int>& fees){
    if (time <= fees[0]) return fees[1];
    time -= fees[0];
    int ret = fees[1];
    ret += (time%fees[2] ? (time+fees[2])/fees[2] : time/fees[2]) * fees[3];
    return ret;
}

vector<int> solution(vector<int> fees, vector<string> records) {
    vector<int> answer;
    
    vector<Record> _records;
    for (auto str: records) {
        istringstream ss(str);
        string s_time, s_car_num, s_in;
        ss >> s_time >> s_car_num >> s_in;

        _records.push_back({time_convert(s_time), stoi(s_car_num), (s_in == "IN")});
    }

    vector<T> cars(10000, {0, 0, false}); // {입/출차 시간, 누적 시간, 입차 여부}
    for (auto record: _records) {
        auto& car = cars[record.car_num];
        if (get<2>(car) == false) { // 마지막 기록이 출차인 경우
            get<0>(car) = record.time; // 현재 입차 시간 기록
            get<2>(car) = true; // 현재 상태를 입차로 바꿈
        } else {
            get<1>(car) += (record.time - get<0>(car)); // '출차시간'-'입차시간' 더해서 누적시간 계산
            get<2>(car) = false; // 현재 상태를 출차로 바꿈
        }
    }

    for (auto record: _records) {
        auto& car = cars[record.car_num];
        if (get<2>(car) == true) { // 마지막 기록이 입차면 강제로 23:59에 출차시킴
            get<1>(car) += (time_convert("23:59") - get<0>(car));
            get<2>(car) = false;
        }
    }

    for (int i = 0; i < cars.size(); i++){
        auto& car = cars[i];
        if (get<1>(car)){
            // cout << "{" << get<0>(car) << ", " << get<1>(car) << ", " << get<2>(car) << "}" << endl;
            answer.push_back(fee_convert(get<1>(car), fees));
        }
    }

    return answer;
}