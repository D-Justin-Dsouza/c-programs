//write a menu driven program to implement heap sort and quick sort
#include<stdio.h>
#include<stdlib.h>
#define MAX 100
int arr[MAX];

void heap_sort(int[], int);
void buildheap(int[], int);
int del_root(int[], int*);
void restoredown(int[], int, int);

void quick_sort(int[], int, int);

int main(){
    int n, i, ch;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    printf("Enter the elements: ");
    for(i=0; i<n; i++)
        scanf("%d", &arr[i]);
    while(1){
        printf("\n1. Heap Sort\n2. Quick Sort\n3. Exit\nEnter your choice: ");
        scanf("%d", &ch);
        switch(ch){
            case 1: heap_sort(arr, n);
                    printf("Sorted array: ");
                    for(i=0; i<n; i++)
                        printf("%d ", arr[i]);
                    break;
            case 2: quick_sort(arr, 0, n-1);
                    printf("Sorted array: ");
                    for(i=0; i<n; i++)
                        printf("%d ", arr[i]);
                    break;
            case 3: exit(0);
            default: printf("Invalid choice\n");
        }
    }
    return 0;
}

void heap_sort(int arr[], int n){
    int max;
    buildheap(arr, n);
    printf("Heap: ");
    for(int i=0; i<n; i++)
        printf("%d ", arr[i]);
    while(n>1){
        max = del_root(arr, &n);
        arr[n] = max;
    }
}

void buildheap(int arr[], int n){
    for(int i=n/2-1; i>=1; i--)
        restoredown(arr, i, n);
}

void restoredown(int arr[], int i, int n){
    int left=2*i, right=2*i+1, num=arr[i];
    while(right<=n){
        if(num>=arr[left] && num>=arr[right]){
            arr[i] = num;
            return;
        }
        else if(arr[left]>arr[right]){
            arr[i] = arr[left];
            i = left;
        }
        else{
            arr[i] = arr[right];
            i = right;
        }
        left = 2*i;
        right = 2*i+1;
    }
    if(left==n && num<arr[left]){
        arr[i] = arr[left];
        i = left;
    }
    arr[i] = num;
}

int del_root(int arr[], int *n){
    int max = arr[0];
    arr[0] = arr[*n-1];
    (*n)--;
    restoredown(arr, 1, *n);
    return max;
}

//take first element as pivot and partition the array, descending order
void quick_sort(int arr[], int low, int high){
    int i, j, pivot, temp;
    if(low<high){
        pivot = low;
        i = low;
        j = high;
        while(i<j){
            while(arr[i]>=arr[pivot] && i<high)
                i++;
            while(arr[j]<arr[pivot])
                j--;
            if(i<j){
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        temp = arr[pivot];
        arr[pivot] = arr[j];
        arr[j] = temp;
        quick_sort(arr, low, j-1);
        quick_sort(arr, j+1, high);
    }
}