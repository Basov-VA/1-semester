#include<vector>
#include<unordered_map>
#include<memory>
#include<map>
using namespace std;


vector<shared_ptr<string>> DeDuplicate(vector<unique_ptr<string>>& in) {
    vector<shared_ptr<string>> out;
    map<string, shared_ptr<string>> map;
    
    for (auto& x : in) {
        auto s = *x;
        if (map.find(s) != map.end()) {
            out.push_back(map[s]);
        } else {
            auto x1 = make_shared<string>(s);
            out.push_back(x1);
            map[s] = x1;
        }
    }
    
    return out;
}

vector<unique_ptr<string>> Duplicate(const vector<shared_ptr<string>>& in) {
    vector<unique_ptr<string>> out;
    
    for (auto& x : in) {
        out.push_back(make_unique<string>(*x));
    }
    return out;
}
