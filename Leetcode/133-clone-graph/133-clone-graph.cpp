/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:    
    unordered_map<Node*, Node*> visited;
    
    Node* dfs(Node* curr){
        if(curr == nullptr) return nullptr;
        
        Node* copied = new Node(curr->val);
        visited[curr] = copied;
        
        for(Node* next: curr->neighbors){
            if(visited.find(next) == visited.end())
                dfs(next);
            
            copied->neighbors.push_back(visited[next]);
        }
        return copied;
    }
    
    Node* cloneGraph(Node* node) {
        return dfs(node); 
    }
};