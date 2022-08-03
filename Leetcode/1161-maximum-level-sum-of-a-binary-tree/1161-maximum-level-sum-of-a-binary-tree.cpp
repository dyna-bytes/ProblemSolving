/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    // level treversal을 하며 level sum을 구함
    int maxLevelSum(TreeNode* root) {
        int minLevel = 0;
        int maxSum = INT_MIN;
        
        queue<TreeNode*> q;
        q.push(root);
        
        int level = 0;
        while(!q.empty()){
            level++;
            int levelSum = 0;
            int qsize = q.size();
            
            for(int i = 0; i < qsize; i++){
                TreeNode* curr = q.front();
                q.pop();
                
                levelSum += (curr->val);
            
                if(curr->left != nullptr) q.push(curr->left);
                if(curr->right != nullptr) q.push(curr->right);
            }
            
            if(maxSum < levelSum){
                maxSum = levelSum;
                minLevel = level;
            }
        }
        
        return minLevel;
    }
};