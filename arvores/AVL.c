#include <stdio.h>
#include <stdlib.h>

// Estrutura para um nó
typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

// Função para obter a altura de um nó
int getHeight(Node* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

// Função para obter o máximo de dois inteiros
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Função para criar um novo nó
Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

// Função para rotacionar à direita a subárvore enraizada em y
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Realizar a rotação
    x->right = y;
    y->left = T2;

    // Atualizar as alturas
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    // Retornar a nova raiz
    return x;
}

// Função para rotacionar à esquerda a subárvore enraizada em x
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Realizar a rotação
    y->left = x;
    x->right = T2;

    // Atualizar as alturas
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    // Retornar a nova raiz
    return y;
}

// Função para obter o fator de balanceamento de um nó
int getBalance(Node* node) {
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

// Função para inserir um nó na árvore AVL
Node* insertNode(Node* node, int key) {
    // Realizar a inserção normal de BST
    if (node == NULL) {
        return createNode(key);
    }

    if (key < node->key) {
        node->left = insertNode(node->left, key);
    } else if (key > node->key) {
        node->right = insertNode(node->right, key);
    } else {
        // Chaves duplicadas não são permitidas na árvore AVL
        return node;
    }

    // Atualizar a altura do nó atual
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // Verificar o fator de balanceamento e realizar rotações, se necessário
    int balance = getBalance(node);

    // Caso Esquerda Esquerda
    if (balance > 1 && key < node->left->key) {
        return rightRotate(node);
    }

    // Caso Direita Direita
    if (balance < -1 && key > node->right->key) {
        return leftRotate(node);
    }

    // Caso Esquerda Direita
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Caso Direita Esquerda
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Retornar o ponteiro do nó inalterado
    return node;
}

// Função para imprimir a árvore AVL em ordem de percurso
void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->key);
        inorderTraversal(root->right);
    }
}

// Código principal
int main() {
    Node* root = NULL;

    // Inserir nós na árvore AVL
    root = insertNode(root, 10);
    root = insertNode(root, 20);
    root = insertNode(root, 30);
    root = insertNode(root, 40);
    root = insertNode(root, 50);
    root = insertNode(root, 25);

    // Imprimir a árvore AVL
    printf("Percurso em ordem da árvore AVL: ");
    inorderTraversal(root);

    return 0;
}