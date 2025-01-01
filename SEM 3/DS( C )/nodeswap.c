#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *prev;
    struct node *next;
};

struct node *start = NULL;

struct node *createlist(struct node *, int);
struct node *addatbeg(struct node *, int);
struct node *addatend(struct node *, int);
struct node *del(struct node *, int);
void display(struct node *);
struct node *swapAdjacent(struct node *);

int main() {
    int n;
    struct Node* start = NULL;

    // Step 1: Create Doubly Linked List
    printf("Enter the number of nodes: ");
    scanf("%d", &n);
    start = createlist(start, n);

    // Step 2: Display Doubly Linked List
    printf("Doubly Linked List:\n");
    display(start);

    // Step 3: Swap Adjacent Nodes
    start = swapAdjacent(start);
    printf("After swapping adjacent nodes:\n");
    display(start);

    return 0;
}

struct node *createlist(struct node *start, int n) {
    int i, info;
    if (n == 0) {
        return start;
    }
    printf("Enter data:");
    scanf("%d", &info);
    start = addatbeg(start, info);

    for (i = 1; i < n; i++) {
        printf("Enter data:");
        scanf("%d", &info);
        start = addatend(start, info);
    }
    return start;
}

struct node *addatbeg(struct node *start, int info) {
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->data = info;
    temp->prev = NULL;
    temp->next = start;

    if (start != NULL) {
        start->prev = temp;
    }

    start = temp;
    return start;
}

struct node *addatend(struct node *start, int info) {
    struct node *p, *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->data = info;
    temp->next = NULL;

    if (start == NULL) {
        temp->prev = NULL;
        return temp;
    }

    p = start;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = temp;
    temp->prev = p;
    return start;
}

struct node *del(struct node *start, int info) {
    struct node *temp = start;
    if (start == NULL) {
        printf("\nList is Empty\n");
        return start;
    }
    while (temp != NULL) {
        if (temp->data == info) {
            if (temp->prev != NULL) {
                temp->prev->next = temp->next;
            } else {
                start = temp->next;
            }
            if (temp->next != NULL) {
                temp->next->prev = temp->prev;
            }
            free(temp);
            return start;
        }
        temp = temp->next;
    }
    printf("\nElement Not found\n");
    return start;
}

void display(struct node *start) {
    struct node *temp = start;
    if (start == NULL) {
        printf("Empty List\n");
        return;
    }
    printf("<-----------------------------------------------------------------\n");
    while (temp != NULL) {
        printf("|%03d|%d|%03d|\t",(int)temp->prev%1000,temp->data,(int)temp->next%1000);
        temp = temp->next;
    }
    printf("\n---------------------------------------------------------------->\n");
}

struct node *swapAdjacent(struct node *start){
    struct node *temp = start;
    while(temp!=NULL && temp->next!=NULL){
        struct node *first= temp;
        struct node *second=temp->next;
        if(first->prev!=NULL)
            first->prev->next=second;
        else
            start=second;
        second->prev=first->prev;
        first->next=second->next;
        if(second->next!=NULL)
            second->next->prev=first;
        second->next=first;
        first->prev=second;
        temp=first->next;
    }
    return start;
}
