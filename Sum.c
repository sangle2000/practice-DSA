#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int sum(int n) {
    if (n == 0) {
        return 0;
    }

    int currentValue = n % 10;

    return currentValue + sum(n / 10);

}

int main(void) {
    int n;

    printf("Enter n:");
    scanf("%d", &n);

    int value = sum(n);

    printf("%d ", value);

    return 0;
}
