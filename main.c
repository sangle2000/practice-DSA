#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node*));

    if (newNode == NULL) {
        exit(1);
    }

    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

void appendNode(struct Node** head, int value) {
    struct Node* newNode = createNode(value);

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newNode;
}

void printList(struct Node* head) {
    struct Node* temp = head;

    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }

    printf("NULL\n");
}

void deleteNode(struct Node** head, int key) {
    struct Node* temp = *head;
    struct Node* prev = NULL;

    if (temp != NULL && temp->data == key) {
        *head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Del thay");
        return;
    }

    prev->next = temp->next;
    free(temp);
}

void insertionSortLinkedList(struct Node** head) {
    struct Node* temp = *head;

    struct Node* sortList = NULL;

    while (temp != NULL) {
        struct Node* nextNode = temp->next;

        if (sortList == NULL || sortList->data >= temp->data) {
            temp->next = sortList;
            sortList = temp;
        } else {
            struct Node* currentNode = sortList;
            while (currentNode->next != NULL && currentNode->next->data < temp->data) {
                currentNode = currentNode->next;
            }

            temp->next = currentNode->next;
            currentNode->next = temp;
        }

        temp = nextNode;
    }

    *head = sortList;
}

int main() {
    struct Node* head = NULL;

    appendNode(&head, 10);
    appendNode(&head, 50);
    appendNode(&head, 25);
    appendNode(&head, 15);
    appendNode(&head, 20);

    printList(head);

    insertionSortLinkedList(&head);
    printList(head);

    return 0;
}
