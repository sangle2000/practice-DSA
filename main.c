#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    int id;
    char* name;
    char* status;
    int avg;
} Student;

Student* createNewStudent(int id, char name[], char status[], int avg) {
    Student* newStudent = (Student*)malloc(sizeof(Student));

    if (newStudent == NULL) {
        printf("Not enough memory!\n");
        exit(1);
    }

    newStudent->id = id;
    newStudent->name = strdup(name);
    newStudent->status = strdup(status);
    newStudent->avg = avg;

    return newStudent;
}

Student** addStudent(Student** students, int* size, int id, char name[], char status[], int avg) {
    Student** temp = realloc(students, (*size + 1) * sizeof(Student*));
    if (temp == NULL) {
        printf("Not enough memory!\n");
        return students;
    }
    students = temp;

    students[*size] = createNewStudent(id, name, status, avg);
    (*size)++;

    return students;
}

void printStudent(Student** students, int size) {
    printf("Print list:\n");
    if (size == 0) {
        printf("Student list is empty!\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        printf("%d - %s - %s - %d\n",
            students[i]->id, students[i]->name, students[i]->status, students[i]->avg);
    }
}

int main(void) {
    Student** students = NULL;
    int size = 0;

    students = addStudent(students, &size, 1, "Sang", "Available", 10);
    students = addStudent(students, &size, 2, "Le", "Available", 9);
    students = addStudent(students, &size, 3, "Ha", "Available", 5);
    students = addStudent(students, &size, 4, "Thanh", "Available", 6);

    printStudent(students, size);

    // TODO: free all memory
    return 0;
}
