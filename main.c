#include <stdio.h>
#include <stdlib.h>

// === Node của cây ===
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// === Queue ===
#define MAX 100

typedef struct Queue {
    Node* data[MAX];
    int front;
    int rear;
} Queue;

void initQueue(Queue* q) {
    q->front = q->rear = 0;
}

int isEmpty(Queue* q) {
    return q->front == q->rear;
}

void enqueue(Queue* q, Node* node) {
    if (q->rear < MAX)
        q->data[q->rear++] = node;
}

Node* dequeue(Queue* q) {
    if (!isEmpty(q))
        return q->data[q->front++];
    return NULL;
}

// === Tạo node mới ===
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// === Tìm node cần xóa ===
Node* findNodeToDelete(Node* root, int val) {
    if (!root) return NULL;

    Queue q;
    initQueue(&q);
    enqueue(&q, root);

    Node* result = NULL;
    while (!isEmpty(&q)) {
        Node* current = dequeue(&q);
        if (current->data == val)
            result = current;

        if (current->left) enqueue(&q, current->left);
        if (current->right) enqueue(&q, current->right);
    }
    return result;
}

// === Tìm node sâu nhất và cha của nó ===
void findDeepestAndParent(Node* root, Node** deepest, Node** parent) {
    if (!root) return;

    Queue q;
    initQueue(&q);
    enqueue(&q, root);

    *parent = NULL;

    while (!isEmpty(&q)) {
        Node* current = dequeue(&q);

        if (current->left) {
            *parent = current;
            enqueue(&q, current->left);
        }

        if (current->right) {
            *parent = current;
            enqueue(&q, current->right);
        }

        *deepest = current;
    }
}

// === Xóa node sâu nhất ===
void deleteDeepest(Node* parent, Node* deepest) {
    if (!parent || !deepest) return;

    if (parent->left == deepest) {
        free(parent->left);
        parent->left = NULL;
    } else if (parent->right == deepest) {
        free(parent->right);
        parent->right = NULL;
    }
}

// === Xóa node có giá trị val ===
void deleteNode(Node* root, int val) {
    if (!root) {
        printf("Cây rỗng.\n");
        return;
    }

    // Nếu cây chỉ có 1 node
    if (!root->left && !root->right) {
        if (root->data == val) {
            free(root);
            root = NULL;
        } else {
            printf("Không tìm thấy phần tử.\n");
        }
        return;
    }

    Node* target = findNodeToDelete(root, val);
    if (!target) {
        printf("Không tìm thấy phần tử.\n");
        return;
    }

    Node* deepest = NULL;
    Node* parent = NULL;
    findDeepestAndParent(root, &deepest, &parent);

    if (deepest) {
        target->data = deepest->data;  // Ghi đè
        deleteDeepest(parent, deepest);
    }
}

// === Duyệt cây Inorder ===
void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// === Demo ===
int main() {
    Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);

    printf("Cây ban đầu (Inorder): ");
    inorder(root);
    printf("\n");

    deleteNode(root, 2);

    printf("Sau khi xoá 2 (Inorder): ");
    inorder(root);
    printf("\n");

    return 0;
}
