#include <stdbool.h>
#include <stdio.h>

int main(void) {
    const int arr1[5] = {104, 523, 75, 20, 4};
    const int arr2[3] = {100, 20, 23};

    bool isSameItem = false;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            if (arr1[i] == arr2[j]) {
                isSameItem = true;
                break;
            }
        }
       if (isSameItem) {
           break;
       }
    }

    isSameItem ? printf("Array 1 and array 2 have the same item!") : printf("Array 1 and array 2 do not have the same item!");

    return 0;
}

