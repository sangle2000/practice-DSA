#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int fibonacci(int n, int memo[]) {
    if (n == 0) {
        memo[0] = 0;
        return 0;
    }
    if (n == 1) {
        memo[1] = 1;
        return 1;
    }

    if (memo[n] != -1) return memo[n];

    int fib1 = fibonacci(n - 1, memo);
    int fib2 = fibonacci(n - 2, memo);

    memo[n - 1] = fib1;
    memo[n - 2] = fib2;

    memo[n] = fib1 + fib2;

    return memo[n];

}

int main(void) {
    int n;

    printf("Enter n:");
    scanf("%d", &n);

    int *memo = (int *)calloc(n + 1, sizeof(int));

    if (memo == NULL) {
        return 0;
    }

    for (int i = 0; i <= n; i++) {
        memo[i] = -1;
    }

    fibonacci(n, memo);

    for (int i = n; i > 0; i--) {
        printf("%d ", memo[i]);
    }

    free(memo);

    return 0;
}
