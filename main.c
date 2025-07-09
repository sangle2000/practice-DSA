#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->data = value;
    newNode->next = NULL;
}

void appendNode(Node** head, int value) {
    Node* newNode = createNode(value);

    Node* temp = *head;

    if (temp == NULL) {
        *head = newNode;
        return;
    }

    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newNode;
}

void deleteNode(Node** head, int value) {
    Node* temp = *head;
    Node* prev = NULL;

    if (temp != NULL && temp->data == value) {
        *head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->data != value) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Cannot find Node %d\n", value);
        return;
    }

    prev->next = temp->next;
    free(temp);
}

void insertNode(Node** head, int value, int position) {
    Node* newNode = createNode(value);
    Node* temp = *head;
    Node* prev = NULL;
    int i = 0;

    if (position == 0) {
        newNode->next = temp;
        *head = newNode;
        return;
    }

    while (i < position && temp != NULL) {
        prev = temp;
        temp = temp->next;
        i++;
    }

    if (i < position) {
        printf("Position out of range\n");
        return;
    }

    prev->next = newNode;
    newNode->next = temp;
}

void printList(Node* head) {
    Node* temp = head;

    if (temp == NULL) {
        printf("Node is NULL");
        return;
    }

    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    Node* head = NULL;

    appendNode(&head, 10);
    appendNode(&head, 14);
    appendNode(&head, 4);

    printList(head);

    deleteNode(&head, 14);

    printList(head);

    deleteNode(&head, 14);
    printList(head);

    insertNode(&head, 20, 1);
    printList(head);

    return 0;
}
