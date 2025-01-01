//implement bogo sort
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#define MAX 11
void bogo_sort(int arr[], int n);
bool is_sorted(int arr[], int n);
void shuffle(int arr[], int n);
//show each pass on terminal
void show(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
void bogo_sort(int arr[], int n) {
    while (!is_sorted(arr, n)) {
        shuffle(arr, n);
    }
}
bool is_sorted(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}
void shuffle(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        int j = rand() % n;
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}
int main() {
    int arr[MAX];
    srand(time(0));
    printf("Enter %d elements: ", MAX);
    for (int i = 0; i < MAX; i++) {
        scanf("%d", &arr[i]);
    }
    bogo_sort(arr, MAX);
    printf("Sorted array: ");
    for (int i = 0; i < MAX; i++) {
        printf("%d ", arr[i]);
    }
    return 0;
}
