#include <stdbool.h>
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

void reverseList(Node** head) {
    Node* temp = *head;

    if (temp == NULL) {
        printf("List is empty");
        return;
    }

    Node* prev = NULL;
    Node* nextNode = NULL;

    while (temp != NULL) {
        nextNode = temp->next;
        temp->next = prev;
        prev = temp;
        temp = nextNode;
    }

    *head = prev;
}

void changeAdjacentElements(Node** head) {
    Node* temp = *head;

    if (temp == NULL) {
        printf("List is empty");
        return;
    }

    Node* prev = NULL;
    Node* nextNode = NULL;

    *head = temp->next;

    while (temp != NULL && temp->next != NULL) {
        Node* nextNextNode = temp->next->next;
        nextNode = temp->next;
        nextNode->next = temp;

        if (prev != NULL) {
            prev->next = nextNode;
        }

        prev = temp;
        temp = nextNextNode;
    }

    if (temp != NULL) {
        prev->next = temp;
    } else {
        prev->next = NULL;
    }
}

Node* insertionSortList(Node* head) {
    Node* currentList = head;

    if (currentList == NULL) {
        printf("List is empty");
        return NULL;
    }

    Node* store = NULL;

    while (currentList != NULL) {
        Node* next = currentList->next;

        if (store == NULL || store->data >= currentList->data) {
            currentList->next = store;
            store = currentList;
        } else {
            Node* temp = store;
            while (temp->next != NULL && temp->next->data < currentList->data ) {
                temp = temp->next;
            }
            currentList->next = temp->next;
            temp->next = currentList;
        }

        currentList = next;
    }

    return store;
}

void bubbleSortList(Node* head) {
    bool isSwap = false;

    if (head == NULL) {
        printf("List is empty");
        return;
    }

    Node* fixedNode = NULL;

    do {
        isSwap = false;

        Node* temp = head;

        while (temp->next != fixedNode) {
            if (temp->data > temp->next->data) {
                int tempData = temp->data;
                temp->data = temp->next->data;
                temp->next->data = tempData;
                isSwap = true;
            }

            temp = temp->next;
        }
        fixedNode = temp;
    } while (isSwap);
}

Node* getMiddleNode(Node* head) {
    if (head == NULL) {
        printf("List is empty");
        return head;
    }

    Node* slow = head;
    Node* fast = head->next;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

Node* sortedMerge(Node* left, Node* right) {
    if (left == NULL) return right;
    if (right == NULL) return left;

    Node* result = NULL;

    if (left->data <= right->data) {
        result = left;
        result->next = sortedMerge(left->next, right);
    } else {
        result = right;
        result->next = sortedMerge(left, right->next);
    }

    return result;
}

Node* mergeSortList(Node* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    Node* middleNode = getMiddleNode(head);
    Node* nextOfMiddle = middleNode->next;

    middleNode->next = NULL;

    Node* left = mergeSortList(head);
    Node* right = mergeSortList(nextOfMiddle);

    return sortedMerge(left, right);
}

int main() {
    Node* head = NULL;

    appendNode(&head, 10);
    appendNode(&head, 14);
    appendNode(&head, 4);
    appendNode(&head, 20);

    printList(head);

    head = mergeSortList(head);

    printList(head);

    // head = insertionSortList(head);
    // printList(head);

    // bubbleSortList(head);
    // printList(head);

    // reverseList(&head);
    // printList(head);

    // changeAdjacentElements(&head);
    // printList(head);

    return 0;
}
