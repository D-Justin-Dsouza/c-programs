#include <stdio.h>
#include <stdlib.h>
#define MAX 100

// Define the structure for the linked list node (for Radix Sort)
struct node {
    char info;
    struct node *link;
};

// Function prototypes for Radix Sort
void radix_sort();
int large_dig();
int digit(char number, char k);

// Function prototypes for Top-Down and Bottom-Up Merge Sort
void merge_sort_topdown(char *arr[], char left, char right);
void merge_sort_bottomup(char *arr[], int n);
void merge(char *arr[], char *temp[], char low1, char up1, char low2, char up2);
void copy(char *arr[], char *temp[], char low, char up);
void merge_pass(char *arr[], char *temp[], int size, int n);

// Global linked list start node (used for Radix Sort)
struct node *start = NULL;

// Menu-driven program
int main() {
    int n, i, choice, arr[MAX];
    
    while (1) {
        printf("\nMenu:\n");
        printf("1. Top-Down Merge Sort\n");
        printf("2. Bottom-Up Merge Sort\n");
        printf("3. Radix Sort (linked list)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        if (choice == 4) {
            break;
        }
        
        if (choice == 3) {
            // Radix Sort linked list input
            int val;
            struct node *temp, *p;
            
            printf("Enter the number of elements: ");
            scanf("%d", &n);
            
            for (i = 0; i < n; i++) {
                printf("Enter element %d: ", i+1);
                scanf("%d", &val);
                temp = (struct node*) malloc(sizeof(struct node));
                temp->info = val;
                temp->link = NULL;
                
                if (start == NULL) {
                    start = temp;
                } else {
                    p = start;
                    while (p->link != NULL) {
                        p = p->link;
                    }
                    p->link = temp;
                }
            }
            
            radix_sort(); // Call Radix Sort
            printf("Sorted list (Radix Sort):\n");
            p = start;
            while (p != NULL) {
                printf("%d ", p->info);
                p = p->link;
            }
            printf("\n");
        } else if (choice == 1 || choice == 2) {
            // Merge Sort input
            printf("Enter the number of elements: ");
            scanf("%d", &n);
            
            printf("Enter the elements: \n");
            for (i = 0; i < n; i++) {
                scanf("%d", &arr[i]);
            }
            
            if (choice == 1) {
                merge_sort_topdown(arr, 0, n - 1);
            } else if (choice == 2) {
                merge_sort_bottomup(arr, n);
            }
            
            printf("Sorted list (Merge Sort): \n");
            for (i = 0; i < n; i++) {
                printf("%d ", arr[i]);
            }
            printf("\n");
        } else {
            printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}

// Radix Sort Implementation

void radix_sort() {
    char i, k, dig, least_sig, most_sig;
    struct node *p, *rear[10], *front[10];
    least_sig = 1;
    most_sig = large_dig();
    
    for (k = least_sig; k <= most_sig; k++) {
        printf("\nPass %d   ", k);
        //display the list after each pass
        p = start;
        while (p != NULL) {
            printf("%d-> ", p->info);
            p = p->link;
        }
        for (i = 0; i <= 9; i++) {
            rear[i] = NULL;
            front[i] = NULL;
        }
        
        for (p = start; p != NULL; p = p->link) {
            dig = digit(p->info, k);
            if (front[dig] == NULL)
                front[dig] = p;
            else
                rear[dig]->link = p;
            rear[dig] = p;
        }
        
        i = 0;
        while (front[i] == NULL) i++;
        start = front[i];
        
        while (i < 9) {
            if (rear[i+1] != NULL)
                rear[i]->link = front[i+1];
            else
                rear[i+1] = rear[i];
            i++;
        }
        rear[9]->link = NULL;
        printf("\n");
    }
}

int large_dig() {
    struct node *p = start;
    char large = 0, ndig = 0;
    
    while (p != NULL) {
        if (p->info > large)
            large = p->info;
        p = p->link;
    }
    
    while (large != 0) {
        ndig++;
        large = large / 10;
    }
    return ndig;
}

int digit(char number, char k) {
    char digit, i;
    for (i = 1; i <= k; i++) {
        digit = number % 10;
        number = number / 10;
    }
    return digit;
}

// Merge Sort Implementation

void merge_sort_topdown(char *arr[], char left, char right) {
    if (left < right) {
        int mid = (left + right) / 2;
        merge_sort_topdown(arr, left, mid);
        merge_sort_topdown(arr, mid + 1, right);
        int temp[MAX];
        merge(arr, temp, left, mid, mid + 1, right);
    }
}

void merge_sort_bottomup(char *arr[], int n) {
    int size;
    char temp[MAX];
    for (size = 1; size < n; size *= 2) {
        merge_pass(arr, temp, size, n);
    }
}

void merge(char *arr[], char *temp[], char low1, char up1, char low2, char up2) {
    char i = low1, j = low2, k = low1;
    
    while (i <= up1 && j <= up2) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
    }
    
    while (i <= up1) {
        temp[k++] = arr[i++];
    }
    
    while (j <= up2) {
        temp[k++] = arr[j++];
    }
    
    copy(arr, temp, low1, up2);
}

void merge_pass(char **arr[], char **temp[], int size, int n) {
    char low1, up1, low2, up2;
    low1 = 0;
    
    while (low1 + size < n) {
        up1 = low1 + size - 1;
        low2 = low1 + size;
        up2 = low2 + size - 1;
        
        if (up2 >= n) {
            up2 = n - 1;
        }
        
        merge(*arr, *temp, low1, up1, low2, up2);
        low1 = up2 + 1;
    }
    
    for (int i = low1; i < n; i++) {
        *temp[i] = *arr[i];
    }
}

void copy(char *arr[], char *temp[], char low, char up) {
    for (int i = low; i <= up; i++) {
        arr[i] = temp[i];
    }
}
