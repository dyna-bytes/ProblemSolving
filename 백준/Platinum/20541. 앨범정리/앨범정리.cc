#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#define endl '\n'
#define debug(x) cout << "[debug] " << #x << " is " << x << endl;
#define debugVec(v) do { \
    cout << "[debug] " << #v << endl; \
    for (auto e: v) cout << e << " | "; \
    cout << endl; \
} while(0);
typedef pair<int, int> pii;
typedef vector<int> vint;
typedef vector<pii> vpii;

pii operator+(const pii& p1, const pii& p2) {
    return {p1.first + p2.first, p1.second + p2.second};
}

typedef string Photo;
const string ERROR_MESSAGE_1 = "duplicated album name";
const string ERROR_MESSAGE_2 = "duplicated photo name";

struct Album {
    string mAlbum;
    Album* parentAlbum;
    map<string, Album*> childAlbumDB;
    set<Photo> photoDB;

    Album () { mAlbum = ""; parentAlbum = nullptr; }
    Album (string _mAlbum) { mAlbum = _mAlbum; parentAlbum = nullptr; }
};

Album* curr_album = nullptr;
Album* root_album = nullptr;

void debug_album(Album* album) {
    cout << "------------------------" << endl;
    cout << "album: " << album->mAlbum << endl;
    cout << "  child albums: " << endl;
    for (auto p: album->childAlbumDB)
        cout << "    " << p.first << endl;

    cout << "  photos: " << endl;
    for (auto s: album->photoDB)
        cout << "    " << s << endl;
}

void init() {
    Album* album = new Album("album");
    curr_album = album;
    root_album = album;
}

int make_album(string mAlbum) {
    if (curr_album->childAlbumDB[mAlbum]) return -1;

    Album* new_album = new Album(mAlbum);
    curr_album->childAlbumDB[mAlbum] = new_album;
    new_album->parentAlbum = curr_album;
    return 0;
}

pii dfs(Album* curr) {
    pii ret = {1, curr->photoDB.size()};
    for (auto [name, next]: curr->childAlbumDB)
        ret = ret + dfs(next);

    // debug_album(curr);
    curr->childAlbumDB.clear();
    curr->photoDB.clear();
    return ret;
}

pii remove_album(string mAlbum) {
    pii ret = {0, 0};
    if (curr_album->childAlbumDB.empty()) return ret;

    if (mAlbum == "-1") {
        Album* fastest = curr_album->childAlbumDB.begin()->second;
        ret = dfs(fastest);
        curr_album->childAlbumDB.erase(fastest->mAlbum);
        return ret; 
    }
    else if (mAlbum == "0") {
        for (auto [_, child]: curr_album->childAlbumDB) 
            ret = ret + dfs(child);
        curr_album->childAlbumDB.clear();
        return ret;
    }
    else if (mAlbum == "1") {
        Album* latest = prev(curr_album->childAlbumDB.end())->second;
        ret = dfs(latest);
        curr_album->childAlbumDB.erase(latest->mAlbum);
        return ret;
    }
    
    if (curr_album->childAlbumDB.find(mAlbum) == curr_album->childAlbumDB.end()) return ret;
    Album* that = curr_album->childAlbumDB[mAlbum];
    ret = dfs(that);
    curr_album->childAlbumDB.erase(mAlbum);
    return ret;
}

int insert_photo(Photo mPhoto) {
    if (curr_album->photoDB.count(mPhoto)) return -1;

    curr_album->photoDB.insert(mPhoto);
    return 0;
}

int delete_photo(Photo mPhoto) {
    if (curr_album->photoDB.empty()) return 0;

    if (mPhoto == "-1") {
        Photo fastest = *(curr_album->photoDB.begin());
        curr_album->photoDB.erase(fastest);
        return 1;
    }
    else if (mPhoto == "0") {
        int ret = curr_album->photoDB.size();
        curr_album->photoDB.clear();
        return ret;
    }
    else if (mPhoto == "1") {
        Photo latest = *(prev(curr_album->photoDB.end()));
        curr_album->photoDB.erase(latest);
        return 1;
    }

    if (curr_album->photoDB.count(mPhoto) == 0) return 0;
    
    curr_album->photoDB.erase(mPhoto);
    return 1;
}

string change_album(string mAlbum) {
    if (mAlbum == "/") {
        curr_album = root_album;
        return curr_album->mAlbum;
    }
    else if (mAlbum == "..") {
        if (curr_album == root_album) return curr_album->mAlbum;

        curr_album = curr_album->parentAlbum;
        return curr_album->mAlbum;
    }

    if (curr_album->childAlbumDB.find(mAlbum) == curr_album->childAlbumDB.end()) return curr_album->mAlbum;
    curr_album = curr_album->childAlbumDB[mAlbum];
    return curr_album->mAlbum;
}


int main() {
    FASTIO;
    int N; cin >> N;
    init();
    for (int i = 0; i < N; i++) {
        string opA, opB;
        cin >> opA >> opB;
        if (opA == "mkalb") {
            int ret = make_album(opB);
            if (ret == -1) cout << ERROR_MESSAGE_1 << endl;
        }
        if (opA == "rmalb") {
            pii ret = remove_album(opB);
            cout << ret.first << " " << ret.second << endl;
        }
        if (opA == "insert") {
            int ret = insert_photo(opB);
            if (ret == -1) cout << ERROR_MESSAGE_2 << endl;
        }
        if (opA == "delete") {
            int ret = delete_photo(opB);
            cout << ret << endl;
        }
        if (opA == "ca") {
            string ret = change_album(opB);
            cout << ret << endl;
        }
    }

    // debug_album(root_album);
    // change_album("animal");
    // debug_album(curr_album);
    // change_album("land");
    // debug_album(curr_album);
    return 0;
}