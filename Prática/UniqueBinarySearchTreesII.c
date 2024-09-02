#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* createNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct TreeNode** generateTrees(int n, int* returnSize) {
    if (n == 0) {
        *returnSize = 0;
        return NULL;
    }
    return generateTreesHelper(1, n, returnSize);
}

struct TreeNode** generateTreesHelper(int start, int end, int* returnSize) {
    struct TreeNode** result = NULL;
    if (start > end) {
        *returnSize = 1;
        result = (struct TreeNode**)malloc(sizeof(struct TreeNode*));
        result[0] = NULL;
        return result;
    }
    *returnSize = 0;
    for (int i = start; i <= end; i++) {
        int leftSize = 0, rightSize = 0;
        struct TreeNode** leftSubtrees = generateTreesHelper(start, i - 1, &leftSize);
        struct TreeNode** rightSubtrees = generateTreesHelper(i + 1, end, &rightSize);
        for (int j = 0; j < leftSize; j++) {
            for (int k = 0; k < rightSize; k++) {
                struct TreeNode* root = createNode(i);
                root->left = leftSubtrees[j];
                root->right = rightSubtrees[k];
                result = (struct TreeNode**)realloc(result, (*returnSize + 1) * sizeof(struct TreeNode*));
                result[*returnSize] = root;
                (*returnSize)++;
            }
        }
        free(leftSubtrees);
        free(rightSubtrees);
    }
    return result;
}
