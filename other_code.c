//
// Created by ADMIN on 29/6/2025.
//

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int hasPairBruteForce(int arr[], int n, int K) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] + arr[j] == K) {
                return 1; // Found
            }
        }
    }
    return 0; // Not found
}

#define MAX 10000 // Giới hạn giá trị số trong mảng

int hasPairHashSet(int arr[], int n, int K) {
    char *hash = (char *)calloc(MAX, sizeof(char));
    if (!hash) {
        printf("Memory allocation failed!\n");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        int target = K - arr[i];
        if (target >= 0 && target < MAX && hash[target]) {
            free(hash);
            return 1;
        }
        if (arr[i] >= 0 && arr[i] < MAX) {
            hash[arr[i]] = 1;
        }
    }

    free(hash);
    return 0;
}

int demo() {
    bool isBreak = false;

    int seats[101] = {0};

    while (!isBreak) {
        int numOfSeats = 0;
        int chosen;
        printf("Please enter the number of seats you want to book (from 1 to 100):");
        scanf("%d", &numOfSeats);

        if (numOfSeats < 0 || numOfSeats > 100) {
            printf("\nSorry, please enter valid number");
            continue;
        }

        printf("Seat free: ");
        for (int i = 0; i < 101; i++) {
            if (seats[i] == 0) {
                printf("%d ", i);
            }
        }

        int seatSelected = 0;

        while (seatSelected < numOfSeats) {
            printf("\nPlease enter the number of seats you want to book (from 1 to 100): ");
            scanf("%d", &chosen);

            if (seats[chosen] == 0) {
                seats[chosen] = 1;
                seatSelected++;
                continue;
            }

            printf("Seat %d has been chosen", chosen);
        }

        isBreak = true;
    }

    return 0;
}

int main(void) {

    const int arr[12] = {1, 8, 9, 6, 10, 0, 3, 7, 2, 4, 5, 4};
    const int n = sizeof(arr) / sizeof(arr[0]);
    const int sum = 10;

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] + arr[j] == sum) {
                printf("Found\n");
            }
        }
    }

    return 0;
}
