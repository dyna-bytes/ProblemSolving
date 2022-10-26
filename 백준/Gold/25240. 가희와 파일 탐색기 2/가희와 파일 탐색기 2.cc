#include <bits/stdc++.h>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define debugVec(v) do { \
    std::cout << "[Debug] ["; \
    for(int i = 0; i < ((v.size())-1); i++) std::cout << v[i] << "|"; \
    std::cout << v[((v.size())-1)] << "]\n"; \
} while(0)
#define debugV2D(v) do { \
    std::cout << "[Debug] [\n"; \
    for(int y = 0; y < (v.size()); y++) { \
        if(v[y].empty()){ std::cout << "  []\n"; continue; } \
        std::cout << "  ["; \
        for(int x = 0; x < ((v[y].size())-1); x++) \
            std::cout << v[y][x] << "|"; \
        std::cout << v[y][(v[y].size())-1] << "]\n"; \
    } \
    std::cout << "]\n"; \
} while(0)
#define endl '\n'
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vint;
typedef vector<pii> vpii;

#define NOTHING 0
#define X 1
#define W 2
#define XW 3
#define R 4
#define RX 5
#define RW 6
#define RXW 7

struct User {
    string user_name;
    vector<string> user_groups;
    User (string name) {
        user_name = name;
    }
};

struct File {
    string file_name;
    User* owner;
    string owned_group;
    int owner_permission;
    int owned_group_permission;
    int other_permission;
    File (string f, string og) {
        file_name = f, owned_group = og;
        owner = nullptr;
    } 
};

unordered_map<string, User*> userDB; // {유저 이름: 유저}
unordered_map<string, File*> fileDB; // {파일 이름: 파일}

void addUser(string user_name, vector<string>& user_groups) {
    User* user = new User(user_name);
    user_groups.push_back(user_name);
    user->user_groups = user_groups;

    userDB[user_name] = user;
}

void addFile(string file_name, string file_permission, string owner, string owned_group) {
    File* file = new File(file_name, owned_group);
    file->owner = userDB[owner];

    file->owner_permission = file_permission[0] - '0';
    file->owned_group_permission = file_permission[1] - '0';
    file->other_permission = file_permission[2] - '0';

    fileDB[file_name] = file;
}

int checkUserPermission(string user_name, string file_name) {
    File* file = fileDB[file_name];
    User* user = userDB[user_name];

    if (file->owner == user) return file->owner_permission;

    for (string user_group: user->user_groups) {
        if (user_group == file->owned_group) 
            return file->owned_group_permission;
    }

    return file->other_permission;
}

int answerQuery(string user_name, string file_name, string operation) {
    // debug(user_name);
    int permission = checkUserPermission(user_name, file_name);
    if (operation == "X") 
        return (permission == X) || (permission == XW) || (permission == RX) || (permission == RXW);
    
    if (operation == "W")
        return (permission == W) || (permission == XW) || (permission == RW) || (permission == RXW);

    if (operation == "R")
        return (permission == R) || (permission == RX) || (permission == RW) || (permission == RXW);
    
    return -1;
}

int main(){
    FASTIO;
    
    int U, F;
    cin >> U >> F;
    cin.ignore();
    for (int i = 0; i < U; i++) {
        string str;
        getline(cin, str);

        istringstream iss(str);
        string strbuf;

        vector<string> vstr;
        while (getline(iss, strbuf, ' ')) 
            vstr.push_back(strbuf);
        
        string user_name = vstr.front();
        vstr.erase(vstr.begin());

        vector<string> user_groups;
        istringstream iss2(vstr.front());
        while (getline(iss2, strbuf, ','))
            user_groups.push_back(strbuf);

        addUser(user_name, user_groups);
    }

    for (int i = 0; i < F; i++) {
        string file_name, file_permission, owner, owned_group;
        cin >> file_name >> file_permission >> owner >> owned_group;
        addFile(file_name, file_permission, owner, owned_group);

        // debug(fileDB[file_name]->file_name);
    }

    int Q;
    cin >> Q;
    for (int i = 0; i < Q; i++) {
        string user_name, file_name, operation;
        cin >> user_name >> file_name >> operation;
        cout << answerQuery(user_name, file_name, operation) << endl;
    }
    return 0;
}