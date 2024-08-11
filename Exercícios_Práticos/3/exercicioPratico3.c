#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* subtreeWithAllDeepest( struct TreeNode* root );
int Depth( struct TreeNode* root );
int Max( int a, int b );
struct TreeNode* IncertNode( struct TreeNode* root, int val );
struct TreeNode* CreateNode( int val );

int main(){
    struct TreeNode* root = NULL;
    root = IncertNode( root, 8 );
    root = IncertNode( root, 7 );
    root = IncertNode( root, 4 );
    root = IncertNode( root, 3 );
    root = IncertNode( root, 2 );
    root = IncertNode( root, 5 );
    root = IncertNode( root, 6 );
    root = IncertNode( root, 11 );
    root = IncertNode( root, 10 );
    root = IncertNode( root, 9 );
    root = IncertNode( root, 12 );
    root = IncertNode( root, 13 );

    struct TreeNode* result = subtreeWithAllDeepest( root );
    printf( "%d\n", result->val );
    return 0;
}

struct TreeNode* IncertNode( struct TreeNode* root, int val ) {
    if( root == NULL ) {
        return CreateNode( val );
    }
    if( val < root->val ) {
        root->left = IncertNode( root->left, val );
    } else {
        root->right = IncertNode( root->right, val );
    }
    return root;
}

struct TreeNode* CreateNode( int val ) {
    struct TreeNode* newNode = ( struct TreeNode* )malloc( sizeof( struct TreeNode ));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct TreeNode* subtreeWithAllDeepest( struct TreeNode* root ) {
    if(root->left == NULL && root->right == NULL) {
        return root;
    }
    int leftDepth = Depth( root->left );
    int rightDepth = Depth( root->right );

    if( leftDepth == rightDepth ) {
        return root;
    } else if( leftDepth > rightDepth ) {
        return subtreeWithAllDeepest( root->left );
    } else {
        return subtreeWithAllDeepest( root->right );
    }
}

int Depth( struct TreeNode* root ) {
    if( root == NULL ) {
        return 0;
    }
    return 1 + Max( Depth( root->left ), Depth( root->right ) );
}

int Max( int a, int b ) {
    return a > b ? a : b;
}