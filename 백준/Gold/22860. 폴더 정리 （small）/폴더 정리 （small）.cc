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

struct File {
    string fileName;
    File () {
        fileName = "";
    }
    File (string name) {
        fileName = name;
    }
};

struct Folder {
    string folderName;
    unordered_set<Folder*> childFolders; 
    unordered_set<File*> childFiles;
    Folder () {
        folderName = "";
        childFolders.clear();
        childFiles.clear();
    }
    Folder (string name) {
        folderName = name;
    }
};

Folder * Main = new Folder("main");
unordered_map<string, Folder*> folderDB;

void dfs(Folder* curr, unordered_map<string, int>& res) {
    // debug(curr->folderName);
    for (File* file: curr->childFiles) 
        res[file->fileName]++;
    
    
    for (Folder* next: curr->childFolders)
        dfs(next, res);
}

void addFolder(string parent_folder, string name) {
    if (folderDB.find(name) == folderDB.end()) {
        Folder * folder = new Folder(name);
        folderDB[name] = folder;
    }

    if (folderDB.find(parent_folder) == folderDB.end()) {
        Folder * parentFolder = new Folder(parent_folder);
        folderDB[parent_folder] = parentFolder;
    }

    (folderDB[parent_folder])->childFolders.insert(folderDB[name]);
}

void addFile(string parent_folder, string name) {
    File * file = new File(name);
    auto it = folderDB.find(parent_folder);

    if (folderDB.find(parent_folder) == folderDB.end()) {
        Folder * parentFolder = new Folder(parent_folder);
        folderDB[parent_folder] = parentFolder;
    }

    (folderDB[parent_folder])->childFiles.insert(file);
}

pii displayFolderInfo(string name) {
    Folder* folder = folderDB[name]; 

    unordered_map<string, int> res;
    dfs(folder, res);

    int sum = 0;
    for (auto [_, count]: res) sum += count;
    return { res.size(), sum };
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

    int Q; cin >> Q;
    for (int i = 0; i < Q; i++) {
        string query; cin >> query;
        
        istringstream iss(query);
        string stringbuffer;
        while (getline(iss, stringbuffer, '/')) {}

        pii res = displayFolderInfo(stringbuffer);
        cout << res.first << " " << res.second << endl;    
    }
    
    return 0;
}