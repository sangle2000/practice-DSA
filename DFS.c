#include <stdlib.h>

#include "stdio.h"

// Cài đặt DFS
// Bước 1: Cấu trúc Node
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Hàm tạo node mới
Node* createNewNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Not enough memory!");
        exit(1);
    }

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// Bước 2: Triển khai DFS bằng đệ quy
// 1. In-Order (LNR)
void inorder(Node* node) {
    if (node != NULL) {
        inorder(node->left);
        printf("%d ", node->data);
        inorder(node->right);
    }
}

// 2. Pre-Order (NLR)
void preorder(Node* node) {
    if (node != NULL) {
        printf("%d ", node->data);
        preorder(node->left);
        preorder(node->right);
    }
}

// 3. Post-Order (LRN)
void postorder(Node* node) {
    if (node != NULL) {
        postorder(node->left);
        postorder(node->right);
        printf("%d ", node->data);
    }
}

// Bước 3: Xây cây triển khai trong main
int main(void) {
    Node* root = createNewNode(1);

    root->left = createNewNode(2);
    root->right = createNewNode(3);
    root->left->left = createNewNode(4);
    root->left->right = createNewNode(5);

    printf("In-Order (LNR): ");
    inorder(root);

    printf("\n");

    printf("Pre-Order (NLR): ");
    preorder(root);

    printf("\n");

    printf("Post-Order (LRN): ");
    postorder(root);

    return 0;
}
