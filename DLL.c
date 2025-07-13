#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node*));

    if (newNode == NULL) {
        printf("Error when create new node");
        exit(1);
    }

    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}

void appendNode(Node** head, int value) {
    Node* temp = *head;
    Node* newNode = createNode(value);

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newNode;
    newNode->prev = temp;
}

void insertNode(Node** head, int value, int pos) {
    Node* temp = *head;
    Node* newNode = createNode(value);

    int count = 0;

    if (temp == NULL) {
        *head = newNode;
        return;
    }

    if (pos == 0) {
        newNode->next = temp;

        *head = newNode;

        return;
    }

    while (temp->next != NULL && count < pos) {
        temp = temp->next;
        count++;
    }

    if (temp->next == NULL && count != pos - 1) {
        printf("Invalid position");
        return;
    }

    if (temp->next == NULL) {
        temp->next = newNode;
        newNode->prev = temp;
        return;
    }

    temp->prev->next = newNode;
    newNode->next = temp;
    newNode->prev = temp->prev;
    temp->next->prev = newNode;
}

void printList(Node* head) {
    Node* temp = head;

    if (temp == NULL) {
        printf("List is empty");
        return;
    }

    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }

    printf("NULL\n");
}

int main() {
    Node* head = NULL;

    appendNode(&head, 10);
    appendNode(&head, 20);
    appendNode(&head, 40);
    appendNode(&head, 15);
    appendNode(&head, 5);

    printList(head);

    insertNode(&head, 25, 3);
    printList(head);

    return 0;
}
