class LRUCache {
public:
    typedef list<int> li; // {key}
    typedef li::iterator pos;
    typedef pair<int, pos> Node; // {value, position}
    typedef unordered_map<int, Node*> unrd_map; // {key, {value, position}}

    int cap;
    li used;
    unrd_map map;

    LRUCache(int capacity) {
        cap = capacity;
    }
    
    int get(int key) {
        auto ret = map.find(key);
        if(ret == map.end()) return -1;

        Node* node = ret->second;
        int value = node->first;
        deleteNode(node);
        insertBack(key, node);
        return value;
    }
    
    void put(int key, int value) {
        if(get(key) != -1){
            map[key]->first = value;
            return;
        }
        
        Node* node = new Node(value, nullptr);
        insertBack(key, node);
        map.insert({key, node});

        if(map.size() > cap){
            int head_key = used.front();
            used.pop_front();
            map.erase(head_key);
        }
    }
private:
    void insertBack(int key, Node* node){
        used.push_back(key);
        pos& node_it = node->second;
        node_it = (--used.end());
    }
    void deleteNode(Node* node){
        pos& node_it = node->second;
        used.erase(node_it);
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */