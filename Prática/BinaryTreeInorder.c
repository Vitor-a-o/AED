#include <stdio.h>
#include <stdlib.h>

int* inorderTraversal(struct TreeNode* root, int* returnSize);

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int main(){
    struct TreeNode* root;

}

int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    if (root == NULL) {
        *returnSize = 0;
        return NULL;
    }
    
    int* result = (int*)malloc(sizeof(int) * 100); // Assuming the maximum number of nodes is 100
    int index = 0;
    
    struct TreeNode* stack[100]; // Assuming the maximum depth of the tree is 100
    int top = -1;
    
    struct TreeNode* current = root;
    
    while (current != NULL || top != -1) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }
        
        current = stack[top--];
        result[index++] = current->val;
        current = current->right;
    }
    
    *returnSize = index;
    return result;
}