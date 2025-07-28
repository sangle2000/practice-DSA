
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

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

Node* insertNode(Node* node, int data) {
    if (node == NULL) {
        return createNewNode(data);
    }

    if (data < node->data) {
        node->left = insertNode(node->left, data);
    } else if (data > node->data) {
        node->right = insertNode(node->right, data);
    } else {
        printf("Node %d already exists!\n", data);
        return NULL;
    }

    return node;
}

void inorder(Node* node) {
    if (node != NULL) {
        inorder(node->left);
        printf("%d ", node->data);
        inorder(node->right);
    }
}

int main(void) {
    Node* root = NULL;
    root = insertNode(root, 50);
    insertNode(root, 30);
    insertNode(root, 70);
    insertNode(root, 20);
    insertNode(root, 40);
    insertNode(root, 60);
    insertNode(root, 80);

    inorder(root);

    printf("\n");

    insertNode(root, 25);
    insertNode(root, 45);

    inorder(root);

    return 0;
}