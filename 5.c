#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_SEQUENCE_SIZE 100

int choice, size, start, initialDirection;
int sequence[MAX_SEQUENCE_SIZE];

void input(int size);
void calculateDistanceFIFO(int start, int sequence[], int size);
void calculateDistanceSSTF(int start, int sequence[], int size);
void calculateDistanceScan(int start, int sequence[], int size, int initialDirection);
void calculateDistanceCScan(int start, int sequence[], int size);

int main() {
    do {
        printf("\nDisk scheduling\n---------------\n");
        printf("1) Enter parameters\n");
        printf("2) Calculate distance to traverse tracks using FIFO\n");
        printf("3) Calculate distance to traverse tracks using SSTF\n");
        printf("4) Calculate distance to traverse tracks using Scan\n");
        printf("5) Calculate distance to traverse tracks using C-Scan\n");
        printf("6) Quit program and free memory\n");
        printf("Enter selection: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter size of sequence: ");
                scanf("%d", &size);
                size = size - 1;
                break;
            case 2:
                input(size);
                calculateDistanceFIFO(start, sequence, size);
                break;
            case 3:
                input(size);
                calculateDistanceSSTF(start, sequence, size);
                break;
            case 4:
                input(size);
                printf("Enter initial direction: (0=decreasing, 1=increasing): ");
                scanf("%d", &initialDirection);
                calculateDistanceScan(start, sequence, size, initialDirection);
                break;
            case 5:
                input(size);
                calculateDistanceCScan(start, sequence, size);
                break;
            case 6:
                printf("Quitting program...\n");
                break;
            default:
                printf("Invalid selection\n");
                break;
        }
    } while (choice != 6);

    return 0;
}

void input(int size) {
    printf("Enter starting track: ");
    scanf("%d", &start);
    printf("Enter sequence of tracks to seek: ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &sequence[i]);
    }
}

void calculateDistanceFIFO(int start, int sequence[], int size) {
    int distance = abs(start - sequence[0]);
    printf("Traversed sequence: %d ", start);
    printf("%d ", sequence[0]);
    for (int i = 1; i < size; i++) {
        printf("%d ", sequence[i]);
        distance += abs(sequence[i] - sequence[i - 1]);
    }
    printf("\nThe distance of the traversed tracks is: %d\n", (distance + start));
}

void calculateDistanceSSTF(int start, int sequence[], int size) {
    int distance = 0;
    bool visited[MAX_SEQUENCE_SIZE] = {false};
    int current = start;
    printf("Traversed sequence: %d ", start);

    for (int i = 0; i < size; i++) {
        int minDistance = INT_MAX;
        int nextIndex = -1;

        for (int j = 0; j < size; j++) {
            if (!visited[j]) {
                int d = abs(current - sequence[j]);
                if (d < minDistance) {
                    minDistance = d;
                    nextIndex = j;
                }
            }
        }

        distance += minDistance;
        current = sequence[nextIndex];
        visited[nextIndex] = true;
        printf("%d ", current);
    }

    printf("\nThe distance of the traversed tracks is: %d\n", (distance + start));
}

void calculateDistanceScan(int start, int sequence[], int size, int initialDirection) {
    int distance = 0;
    bool visited[MAX_SEQUENCE_SIZE] = {false};
    int current = start;
    printf("Traversed sequence: %d ", start);

    if (initialDirection == 1) {
        // Increasing direction
        for (int i = start; i <= 100; i++) {
            for (int j = 0; j < size; j++) {
                if (sequence[j] == i && !visited[j]) {
                    distance += abs(current - i);
                    current = i;
                    visited[j] = true;
                    printf("%d ", current);
                }
            }
        }

        for (int i = 99; i >= 0; i--) {
            for (int j = 0; j < size; j++) {
                if (sequence[j] == i && !visited[j]) {
                    distance += abs(current - i);
                    current = i;
                    visited[j] = true;
                    printf("%d ", current);
                }
            }
        }
    } else {
        // Decreasing direction
        for (int i = start; i >= 0; i--) {
            for (int j = 0; j < size; j++) {
                if (sequence[j] == i && !visited[j]) {
                    distance += abs(current - i);
                    current = i;
                    visited[j] = true;
                    printf("%d ", current);
                }
            }
        }

        for (int i = 1; i <= 100; i++) {
            for (int j = 0; j < size; j++) {
                if (sequence[j] == i && !visited[j]) {
                    distance += abs(current - i);
                    current = i;
                    visited[j] = true;
                    printf("%d ", current);
                }
            }
        }
    }

    printf("\nThe distance of the traversed tracks is: %d\n", (distance + start));
}

void calculateDistanceCScan(int start, int sequence[], int size) {
    int distance = 0;
    bool visited[MAX_SEQUENCE_SIZE] = {false};
    int current = start;
    printf("Traversed sequence: %d ", start);

    // Find the maximum track in the sequence
    int maxTrack = sequence[0];
    for (int i = 1; i < size; i++) {
        if (sequence[i] > maxTrack)
            maxTrack = sequence[i];
    }

    // Traversing in increasing order till the maximum track
    for (int i = start; i <= maxTrack; i++) {
        for (int j = 0; j < size; j++) {
            if (sequence[j] == i && !visited[j]) {
                distance += abs(current - i);
                current = i;
                visited[j] = true;
                printf("%d ", current);
            }
        }
    }

    // If there are tracks left, traverse to the beginning
    for (int i = 0; i < start; i++) {
        for (int j = 0; j < size; j++) {
            if (sequence[j] == i && !visited[j]) {
                distance += abs(current - i);
                current = i;
                visited[j] = true;
                printf("%d ", current);
            }
        }
    }

    printf("\nThe distance of the traversed tracks is: %d\n", (distance + start));
}