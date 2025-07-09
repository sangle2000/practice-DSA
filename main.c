#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc((sizeof(Node)));
    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

void appendNode(Node** head, int value) {
    Node* newNode = createNode(value);

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newNode;
}

void deleteNode(Node** head, int value) {
    Node* temp = head;
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
        printf("Cannot find node");
        return;
    }

    prev->next = temp->next;
    free(temp);
}

void printList(Node* head) {
    Node* temp = head;

    while (temp->next != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }

    printf("NULL\n");
}

int main() {
    Node* head = NULL;

    appendNode(&head, 10);
    appendNode(&head, 28);
    appendNode(&head, 13);
    appendNode(&head, 5);

    printList(head);

    return 0;
}
