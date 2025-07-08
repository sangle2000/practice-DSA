#include <stdio.h>
#include <stdlib.h>

int main() {
    int arr[5] = { 10, 5, 3, 9, 2 };

    int X = 7;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4 - i; j++) {
            if (abs(X - arr[j]) > abs(X - arr[j + 1])) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            } else if ((abs(X - arr[j]) == abs(X - arr[j + 1])) && (arr[j] > arr[j + 1])) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }

    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
