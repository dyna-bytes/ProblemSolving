#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#define endl '\n'
#define debug(x) cout << "[debug] " << #x << " is " << x <<  endl;
typedef pair<int, int> pii;
typedef vector<int> vint;
typedef vector<pii> vpii;
#define FOLDER 1
#define FILE 0

struct Folder {
    string folderName;
    Folder* parentFolder;
    unordered_set<Folder*> childFolders; 
    unordered_set<string> childFiles;
    Folder () {
        folderName = "";
        childFolders.clear();
        childFiles.clear();
    }
    Folder (string name) {
        folderName = name;
        parentFolder = nullptr;
    }
    ~Folder () {
        childFolders.clear();
        unordered_set<Folder*>().swap(childFolders);

        childFiles.clear();
        unordered_set<string>().swap(childFiles);

        folderName.clear();
        parentFolder = nullptr;
    }
};

Folder * Main = new Folder("main");
unordered_map<string, Folder*> folderDB;

void dfs(Folder* curr, unordered_map<string, int>& res) {
    // debug(curr->folderName);
    for (string file: curr->childFiles) 
        res[file]++;
    
    for (Folder* next: curr->childFolders)
        dfs(next, res);
}

void addFolder(string parent_folder, string name) {
    Folder* folder = nullptr;
    if (folderDB.find(name) == folderDB.end()) {
        folder = new Folder(name);
        folderDB[name] = folder;
    }
    folder = folderDB[name];

    Folder* parentFolder = nullptr;
    if (folderDB.find(parent_folder) == folderDB.end()) {
        parentFolder = new Folder(parent_folder);
        folderDB[parent_folder] = parentFolder;
    }
    parentFolder = folderDB[parent_folder];

    folder->parentFolder = parentFolder;
    parentFolder->childFolders.insert(folder);
}

void addFile(string parent_folder, string file) {
    Folder * parentFolder;
    if (folderDB.find(parent_folder) == folderDB.end()) {
        parentFolder = new Folder(parent_folder);
        folderDB[parent_folder] = parentFolder;
    }
    parentFolder = folderDB[parent_folder];

    parentFolder->childFiles.insert(file);
}

pii displayFolderInfo(string name) {
    Folder* folder = folderDB[name]; 

    unordered_map<string, int> res;
    dfs(folder, res);

    int sum = 0;
    for (auto [_, count]: res) sum += count;
    return { res.size(), sum };
}

void mergeFolder(string start, string dest) {
    Folder* from = folderDB[start];
    Folder* to = folderDB[dest];

    to->childFiles.insert(from->childFiles.begin(), from->childFiles.end());
    to->childFolders.insert(from->childFolders.begin(), from->childFolders.end());

    from->parentFolder->childFolders.erase(from);
    for (Folder* childFolder: from->childFolders) {
        childFolder->parentFolder = to;
    }

    from->~Folder();
}

int main(){
    FASTIO
    int folderNum, fileNum;
    cin >> folderNum >> fileNum;

    folderDB["main"] = Main;

    for (int i = 0; i < folderNum + fileNum; i++) {
        string parent_folder, name;
        int type;
        cin >> parent_folder >> name >> type;

        if (type == FOLDER) 
            addFolder(parent_folder, name);
        else 
            addFile(parent_folder, name);
    }

    int K; cin >> K;
    for (int i = 0; i < K; i++) {
        string query1, query2;
        cin >> query1 >> query2;

        istringstream iss1(query1), iss2(query2);
        string strbuf1, strbuf2;
        
        while (getline(iss1, strbuf1, '/')) {}
        while (getline(iss2, strbuf2, '/')) {}
        mergeFolder(strbuf1, strbuf2);
    }

    int Q; cin >> Q;
    for (int i = 0; i < Q; i++) {
        string query; cin >> query;
        
        istringstream iss(query);
        string stringbuffer;
        while (getline(iss, stringbuffer, '/')) {}

        pii res = displayFolderInfo(stringbuffer);
        cout << res.first << " " << res.second << endl;    
    }
    
    // debug(folderDB["FolderA"]->parentFolder->folderName);
    // debug(folderDB["FolderB"]->parentFolder->folderName);
    // debug(folderDB["FolderC"]->parentFolder->folderName);
    return 0;
}