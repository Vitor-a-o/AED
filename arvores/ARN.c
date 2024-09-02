#include <stdio.h>
#include <stdlib.h>

// Structure for a node
typedef struct Node {
    int data;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
    int color;
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->color = 1; // 1 for red, 0 for black
    return newNode;
}

// Function to perform left rotation
void leftRotate(Node** root, Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        (*root) = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

// Function to perform right rotation
void rightRotate(Node** root, Node* y) {
    Node* x = y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == NULL)
        (*root) = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->right = y;
    y->parent = x;
}

// Function to fix the Red-Black Tree after insertion
void fixInsert(Node** root, Node* newNode) {
    Node* parent = NULL;
    Node* grandparent = NULL;
    while ((newNode != (*root)) && (newNode->color != 0) && (newNode->parent->color == 1)) {
        parent = newNode->parent;
        grandparent = newNode->parent->parent;
        // Case 1: Parent is left child of grandparent
        if (parent == grandparent->left) {
            Node* uncle = grandparent->right;
            // Case 1.1: Uncle is also red, only recoloring is required
            if (uncle != NULL && uncle->color == 1) {
                grandparent->color = 1;
                parent->color = 0;
                uncle->color = 0;
                newNode = grandparent;
            } else {
                // Case 1.2: newNode is right child of parent, left rotation is required
                if (newNode == parent->right) {
                    leftRotate(root, parent);
                    newNode = parent;
                    parent = newNode->parent;
                }
                // Case 1.3: newNode is left child of parent, right rotation is required
                rightRotate(root, grandparent);
                int temp = parent->color;
                parent->color = grandparent->color;
                grandparent->color = temp;
                newNode = parent;
            }
        }
        // Case 2: Parent is right child of grandparent
        else {
            Node* uncle = grandparent->left;
            // Case 2.1: Uncle is also red, only recoloring is required
            if ((uncle != NULL) && (uncle->color == 1)) {
                grandparent->color = 1;
                parent->color = 0;
                uncle->color = 0;
                newNode = grandparent;
            } else {
                // Case 2.2: newNode is left child of parent, right rotation is required
                if (newNode == parent->left) {
                    rightRotate(root, parent);
                    newNode = parent;
                    parent = newNode->parent;
                }
                // Case 2.3: newNode is right child of parent, left rotation is required
                leftRotate(root, grandparent);
                int temp = parent->color;
                parent->color = grandparent->color;
                grandparent->color = temp;
                newNode = parent;
            }
        }
    }
    (*root)->color = 0; // Root node is always black
}

// Function to insert a node in the Red-Black Tree
void insert(Node** root, int data) {
    Node* newNode = createNode(data);
    Node* current = (*root);
    Node* parent = NULL;
    while (current != NULL) {
        parent = current;
        if (newNode->data < current->data)
            current = current->left;
        else
            current = current->right;
    }
    newNode->parent = parent;
    if (parent == NULL)
        (*root) = newNode;
    else if (newNode->data < parent->data)
        parent->left = newNode;
    else
        parent->right = newNode;
    fixInsert(root, newNode);
}

// Function to print the Red-Black Tree in inorder traversal
void inorder(Node* root) {
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

int main() {
    Node* root = NULL;
    insert(&root, 7);
    insert(&root, 3);
    insert(&root, 18);
    insert(&root, 10);
    insert(&root, 22);
    insert(&root, 8);
    insert(&root, 11);
    insert(&root, 26);
    printf("Inorder traversal of the Red-Black Tree: ");
    inorder(root);
    return 0;
}