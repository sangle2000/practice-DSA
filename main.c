#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    int height;
    struct Node *left, *right;
} Node;

/* ------------ Tiện ích cơ bản ------------ */
int height(Node *n) {
    return n ? n->height : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node *newNode(int key) {
    Node *n = (Node*)malloc(sizeof(Node));
    n->key = key;
    n->left = n->right = NULL;
    n->height = 1; // node mới thêm là lá
    return n;
}

/* ------------ Các phép xoay ------------ */
Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    // xoay
    x->right = y;
    y->left  = T2;

    // cập nhật height
    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x; // root mới
}

Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    // xoay
    y->left  = x;
    x->right = T2;

    // cập nhật height
    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y; // root mới
}

int getBalance(Node *n) {
    return n ? height(n->left) - height(n->right) : 0;
}

/* ------------ Chèn (insert) ------------ */
Node *insert(Node *node, int key) {
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left  = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // không cho phép key trùng (tùy bạn xử lý)
        return node;

    // cập nhật height
    node->height = 1 + max(height(node->left), height(node->right));

    // kiểm tra và cân bằng
    int balance = getBalance(node);

    // 4 case
    // Left Left
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

/* ------------ Xóa (delete) ------------ */
Node *minValueNode(Node *node) {
    Node *current = node;
    while (current->left)
        current = current->left;
    return current;
}

Node *deleteNode(Node *root, int key) {
    if (root == NULL)
        return root;

    // BST delete bình thường
    if (key < root->key)
        root->left  = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // node cần xóa
        if (root->left == NULL || root->right == NULL) {
            Node *temp = root->left ? root->left : root->right;
            if (!temp) {
                // không có con
                temp = root;
                root = NULL;
            } else {
                // một con
                *root = *temp; // copy nội dung
            }
            free(temp);
        } else {
            // hai con: lấy inorder successor (nhỏ nhất bên phải)
            Node *temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // Nếu cây chỉ còn NULL
    if (root == NULL)
        return root;

    // cập nhật height
    root->height = 1 + max(height(root->left), height(root->right));

    // cân bằng
    int balance = getBalance(root);

    // Left Left
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

/* ------------ Duyệt cây ------------ */
void preOrder(Node *root) {
    if (root) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(Node *root) {
    if (root) {
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}

/* ------------ Demo ------------ */
int main(void) {
    Node *root = NULL;

    int keys[] = {10, 20, 30, 40, 50, 25};
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < n; ++i)
        root = insert(root, keys[i]);

    printf("Preorder sau khi chen: ");
    preOrder(root);
    printf("\n");

    printf("Inorder  sau khi chen: ");
    inOrder(root);
    printf("\n");

    root = deleteNode(root, 40);
    printf("Preorder sau khi xoa 40: ");
    preOrder(root);
    printf("\n");

    return 0;
}
