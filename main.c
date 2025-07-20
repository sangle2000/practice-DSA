
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person {
    char* name;
    int age;
    struct Person* next;
} Person;

typedef struct QueuePerson {
    Person* head;
    Person* tail;
} QueuePerson;

Person* createPersonQueue(char name[], int age) {
    Person* newPerson = (Person*)malloc(sizeof(Person));

    if (newPerson == NULL) {
        printf("Memory is not enough!");
        exit(1);
    }

    newPerson->name = strdup(name);
    newPerson->age = age;
    newPerson->next = NULL;

    return newPerson;
}

int isEmpty(QueuePerson* queuePerson) {
    return queuePerson->head == NULL;
}

void enqueuePerson(QueuePerson* queuePerson, char name[], int age) {
    Person* newPerson = createPersonQueue(name, age);
    if (queuePerson->head == NULL) {
        queuePerson->head = newPerson;
        queuePerson->tail = newPerson;
        return;
    }

    queuePerson->tail->next = newPerson;
    queuePerson->tail = newPerson;
}

void dequeuePerson(QueuePerson* queueOldPerson, QueuePerson* queueNormalPerson) {
    Person* temp = NULL;

    if (!isEmpty(queueOldPerson)) {
        temp = queueOldPerson->head;
        queueOldPerson->head = queueOldPerson->head->next;
        if (queueOldPerson->head == NULL) queueOldPerson->tail = NULL;
    } else if (!isEmpty(queueNormalPerson)) {
        temp = queueNormalPerson->head;
        queueNormalPerson->head = queueNormalPerson->head->next;
        if (queueNormalPerson->head == NULL) queueNormalPerson->tail = NULL;
    }

    if (temp == NULL) {
        printf("Queue is empty!\n");
        return;
    }

    printf("Person: %s (age %d)\n", temp->name, temp->age);
    free(temp->name);
    free(temp);
}

int main(void) {
    // Cấp phát queue trước khi dùng
    QueuePerson* queueOldPerson = (QueuePerson*)malloc(sizeof(QueuePerson));
    queueOldPerson->head = queueOldPerson->tail = NULL;

    QueuePerson* queueNormalPerson = (QueuePerson*)malloc(sizeof(QueuePerson));
    queueNormalPerson->head = queueNormalPerson->tail = NULL;

    int chosen = -1;

    while (chosen != 0) {
        printf("1. Add person\n");
        printf("2. Get person\n");
        printf("0. Exit\n");

        scanf("%d", &chosen);
        getchar();  // để loại bỏ newline sau scanf

        switch (chosen) {
            case 1: {
                char personName[20];
                int age;

                printf("Enter name: ");
                fgets(personName, sizeof(personName), stdin);
                personName[strcspn(personName, "\n")] = '\0';

                printf("Enter age: ");
                scanf("%d", &age);
                getchar(); // xóa newline

                if (age >= 60) {
                    enqueuePerson(queueOldPerson, personName, age);
                } else {
                    enqueuePerson(queueNormalPerson, personName, age);
                }
                break;
            }

            case 2:
                dequeuePerson(queueOldPerson, queueNormalPerson);
                break;

            case 0:
                printf("Exit!\n");
                break;

            default:
                printf("Invalid input!\n");
        }
    }

    return 0;
}
