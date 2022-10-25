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
    for (File* file: curr->childFiles) {
        // debug(file->fileName);
        res[file->fileName]++;
    }
    
    for (Folder* next: curr->childFolders)
        dfs(next, res);
}

int main(){
    int folderNum, fileNum;
    cin >> folderNum >> fileNum;

    folderDB["main"] = Main;

    for (int i = 0; i < folderNum + fileNum; i++) {
        string parent_folder, name;
        int type;
        cin >> parent_folder >> name >> type;

        if (type == FOLDER) {
            if (folderDB.find(name) == folderDB.end()) {
                Folder * folder = new Folder(name);
                folderDB[name] = folder;
            }

            if (folderDB.find(parent_folder) == folderDB.end()) {
                Folder * parentFolder = new Folder(parent_folder);
                folderDB[parent_folder] = parentFolder;
            }

            (folderDB[parent_folder])->childFolders.insert(folderDB[name]);
        } else {
            File * file = new File(name);
            auto it = folderDB.find(parent_folder);

            if (folderDB.find(parent_folder) == folderDB.end()) {
                Folder * parentFolder = new Folder(parent_folder);
                folderDB[parent_folder] = parentFolder;
            }

            (folderDB[parent_folder])->childFiles.insert(file);
        }
    }

    int Q; cin >> Q;
    for (int i = 0; i < Q; i++) {
        string query; cin >> query;
        
        istringstream iss(query);
        string stringbuffer;
        while (getline(iss, stringbuffer, '/')) {}

        Folder* last = folderDB[stringbuffer];       

        unordered_map<string, int> res;
        dfs(last, res);
        int sum = 0;
        for (auto [_, count]: res) sum += count;
        cout << res.size() << " " << sum << endl;
    }
    
    // auto it = folderDB.find("main");
    // for (auto e: it->second->childFolders)
    //     cout << e->folderName << endl;
    return 0;
}