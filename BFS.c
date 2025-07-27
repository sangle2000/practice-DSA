#include "stdio.h"
#include "stdlib.h"
#define MAX_QUEUE 100

// Bước 1: Tạo cấu trúc cây nhị phân
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Bước 2: Tạo hàm tạo node mới cho cây
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

// Bước 3: Tạo cấu trúc hàng đợi (kết hợp mảng hoặc danh sách liên kết)
typedef struct Queue {
    Node* node[MAX_QUEUE];
    int front;
    int rear;
} Queue;

// Bước 4: Tạo các hàm xử lý với hàng đợi (Khởi tạo hàng đợi, kiểm tra hàng đợi có rỗng hay không, thêm, xóa phần tử)
void initQueue(Queue *queue) {
    queue->front = 0;
    queue->rear = -1;
}

int isEmpty(Queue *queue) {
    return queue->front > queue->rear;
}

int isFull(Queue *queue) {
    return queue->rear == MAX_QUEUE;
}

void enQueue(Queue *queue, Node* node) {
    if (!isFull(queue)) {
        queue->rear++;
        queue->node[queue->rear] = node;
        return;
    }

    printf("Queue is full!");
}

Node* deQueue(Queue *queue) {
    if (!isEmpty(queue)) {
        Node* node = queue->node[queue->front];
        queue->front++;

        return node;
    }

    printf("Queue is empty!");
    return NULL;
}

// Bước 5: Triển khai thuật toán duyệt theo chiều rộng (BFS)
void levelOrder(Node *node) {
    if (node == NULL) {
        return;
    }

    Queue q;
    initQueue(&q);
    enQueue(&q, node);

    // Tiến hành duyệt
    while (!isEmpty(&q)) {
        Node* current = deQueue(&q);
        printf("%d ", current->data);

        if (current->left != NULL) {
            enQueue(&q, current->left);
        }

        if (current->right != NULL) {
            enQueue(&q, current->right);
        }
    }
}


// Bước 6: Tạo cây triển khai trong main
int main(void) {
    Node* root = createNewNode(1);

    root->left = createNewNode(2);
    root->right = createNewNode(3);

    root->left->left = createNewNode(4);
    root->left->right = createNewNode(5);

    root->right->left = createNewNode(6);

    levelOrder(root);

    return 0;
}
