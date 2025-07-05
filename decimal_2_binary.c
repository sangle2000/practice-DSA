#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void Decimal2Binary(int number, char *arr, int size) {
    if (size == 0) {
        arr[0] = '\0';
        return;
    }

    arr[0] = (number >> (size - 1)) & 1 ? '1' : '0';

    Decimal2Binary(number, arr + 1, size - 1);
}

int main(void) {
    int n;

    printf("Enter n:");
    scanf("%d", &n);

    int size = (int)log2(n) + 1;

    printf("%d", size);

    char *arr = (char *)malloc(size + 1);

    if (arr == NULL) {
        return 0;
    }

    Decimal2Binary(n, arr, size);

    printf("\n%s", arr);

    free(arr);

    return 0;
}
