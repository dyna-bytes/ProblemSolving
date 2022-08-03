class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> ret;
        unordered_map<string, vector<string>> map;

        for(const auto& s: strs){
            string t = s;
            sort(t.begin(), t.end());
            map[t].push_back(s);
        }

        ret.reserve(map.size());
        for(auto& pair: map){
            ret.push_back(std::move(pair.second));
        }
        return ret;
    }
};